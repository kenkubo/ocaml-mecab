#include <mecab.h>
#include <stdio.h>
#include <string.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/mlvalues.h>


CAMLprim value caml_parse_to_str(value ml_sentence)
{
  CAMLparam1(ml_sentence);
  CAMLlocal1(result);
  mecab_model_t *model = mecab_model_new2("");
  mecab_t *mecab = mecab_model_new_tagger(model);
  mecab_lattice_t *lattice = mecab_model_new_lattice(model);
  const char *sentence = String_val(ml_sentence);
  mecab_lattice_set_sentence(lattice, sentence);
  mecab_parse_lattice(mecab, lattice);
  const char *out = mecab_lattice_tostr(lattice);
  result = caml_copy_string(out);
  mecab_lattice_destroy(lattice);
  mecab_destroy(mecab);
  mecab_model_destroy(model);
  CAMLreturn(result);
}

CAMLprim value caml_parse_to_nodes(value ml_sentence)
{
  CAMLparam1(ml_sentence);
  CAMLlocal4(node_list, cons, ml_surface, ml_tpl);

  const mecab_node_t *node;
  mecab_model_t *model = mecab_model_new2("");
  mecab_t *mecab = mecab_model_new_tagger(model);
  mecab_lattice_t *lattice = mecab_model_new_lattice(model);
  const char *sentence = String_val(ml_sentence);
  
  mecab_lattice_set_sentence(lattice, sentence);
  mecab_parse_lattice(mecab, lattice);
  
  node_list = Val_emptylist;

  node = mecab_lattice_get_eos_node(lattice);
  for (;  node; node = node->prev) {
  
    if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {

      ml_surface = caml_alloc_string (node->length);
      memcpy( String_val(ml_surface), node->surface, node->length );
      cons = caml_alloc(2, 0);
      ml_tpl = caml_alloc(2, 0);

      // pair 
      Store_field( ml_tpl, 0, ml_surface);
      Store_field( ml_tpl, 1, caml_copy_string(node->feature));
      
      // add to node list
      Store_field( cons, 0, ml_tpl );
      Store_field( cons, 1, node_list );
      
      node_list = cons;
    }
  }
  mecab_lattice_destroy(lattice);
  mecab_destroy(mecab);
  mecab_model_destroy(model);
  CAMLreturn(node_list);
}

