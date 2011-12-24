(* $Id: test-compile-warning.pas 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give a compiler warning and fail with NO-OUTPUT
 *
 * @EXPECTED_RESULTS@: NO-OUTPUT
 *)

program warning(input, output);

var
   a : integer;

begin
   a := 1;
end.
