type node = { surface : string; feature : string; }
external mecab_parse_to_str : string -> string = "caml_parse_to_str"
external mecab_parse : string -> (string * string) list
  = "caml_parse_to_nodes"
