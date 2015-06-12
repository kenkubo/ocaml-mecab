open Mecab

let () =
  List.iter 
    (fun (sur,fea) -> 
      print_endline (sur ^ "\t" ^fea))
    (mecab_parse "太郎は次郎が持っている本を花子に渡した。");
  Gc.full_major();
  List.iter 
    (fun (sur,fea) -> 
      print_endline (sur ^ "\t" ^fea))
    (mecab_parse "子供の蹴ったボールを避けようと80代男性が転倒、1年半後に肺炎で死亡…親の監督責任めぐり最高裁で弁論へ");
  Gc.full_major();
  List.iter 
    (fun (sur,fea) -> 
      print_endline (sur ^ "\t" ^fea))
    (mecab_parse "自転車の男性が中学生に追突し死亡");
    
