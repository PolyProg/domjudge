(* $Id: test-hello.p 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give CORRECT on the default problem 'hello'.
 *
 * @EXPECTED_RESULTS@: CORRECT
 *)

program helloworld(input, output);

var
   hello : string;

begin
   hello := 'Hello world!';
   writeln(hello);
end.
