# Configuration file for polygon2domjudge
# Local/selection contest 2015

setPolygonContestId(3116)  # Needed to find the correct package file
setDomjudgeContestId(3)
addLanguage("english")     # Call this method for every language you have statements in, and before calling add problem

# Now here we list all problems:
# Arguments of addProblem:
#  folder = name of the problem in Polygon
#  probid = id to give to the problem in Domjudge (max 8 letters)
#  depends: leave to false, this is only for HC2 (means that this problem is not shown before the previous one was solved)
#  color  = color of the balloon
#  offline: don't set, this is only for HC2 for an offline problem (set to the testcase number to use as the test)
#  runtime = runtime in seconds, leave blank to use the one from Polygon
#  special_runtime = use two integers separated by a comma "2,3" sets the runtime for
#                    Java/Scala (first integer) and Python/Ruby (second integer)
#                    You must adhere to the format even if there is no Python/Ruby/Scala in the contest
#                    Per default, uses the Domjudge multiplier (which is floor(1.5*runtime) for Java)
#  compare = name of the script that checks the solution of the contestant. Per default, uses the one from Polygon.
#  run: name of a special runscript, used for HC2
addProblem(folder="tuples",                          probid="A_tuples", color="red")
addProblem(folder="bombs",                           probid="B_bombs",  color="orange")

if False:
  addLanguage("english")
  addLanguage("french")
  addLanguage("german")
  # Main contest
  setPolygonContestId(2302)
  setDomjudgeContestId(2)
  addProblem(folder="fantastic-four-1",              probid="A_fant0",  depends=False, color="lightyellow", offline=3, runtime=1, special_runtime="2,2")
  addProblem(folder="fantastic-four-2",              probid="B_fant1",  depends=False, color="lemonchiffon", run="fanfour2", runtime=2, special_runtime="7,7")
  addProblem(folder="fantastic-four-3",              probid="C_fant2",  depends=True,  color="yellow",       run="fanfour3", runtime=1, special_runtime="2,7")
  addProblem(folder="fantastic-four-4",              probid="D_fant3",  depends=True,  color="goldenrod",    run="fanfour4", runtime=2, special_runtime="3,7")

  addProblem(folder="hc2-planet-destruction-easy",   probid="E_pland1", depends=False, color="lightblue", runtime=1, special_runtime="2,2")
  addProblem(folder="hc2-planet-destruction-med",    probid="F_pland2", depends=True,  color="skyblue", runtime=2, special_runtime="7,18")
  addProblem(folder="hc2-planet-destruction-hard",   probid="G_pland3", depends=True,  color="deepskyblue", runtime=2, special_runtime="7,5")

  addProblem(folder="synchronizing-automata-easy",   probid="H_hgath1", depends=False, color="whitesmoke", runtime=1, special_runtime="2,2")
  addProblem(folder="synchronizing-automata-medium", probid="I_hgath2", depends=True,  color="gainsboro", runtime=1, special_runtime="2,2")
  addProblem(folder="synchronizing-automata-hard",   probid="J_hgath3", depends=True,  color="silver",       compare="sync3", runtime=1, special_runtime="2,2")

  addProblem(folder="recognize-shape-easy",          probid="K_shape1", depends=False, color="palegreen", runtime=1, special_runtime="2,2")
  addProblem(folder="recognize-shape-medium",        probid="L_shape2", depends=True,  color="limegreen", runtime=1, special_runtime="5,5")
  addProblem(folder="recognize-shape-hard",          probid="M_shape3", depends=True,  color="green", runtime=1, special_runtime="5,5")

  addProblem(folder="counting-numbers-easy",         probid="N_shiel1", depends=False, color="lightcoral", runtime=1, special_runtime="2,2")
  addProblem(folder="counting-numbers-medium",       probid="O_shiel2", depends=True,  color="red", runtime=1, special_runtime="3,3")
  addProblem(folder="counting-numbers-hard",         probid="P_shiel3", depends=True,  color="darkred", runtime=1, special_runtime="10,12")

  # Dry run
  setPolygonContestId(2441)
  setDomjudgeContestId(3)
  addProblem(folder="hc2-dryrun-easy",               probid="A_dry1",   depends=False, color="lavender", runtime=1, special_runtime="2,2")
  addProblem(folder="hc2-dryrun-medium",             probid="B_dry2",   depends=True,  color="mediumpurple", runtime=1, special_runtime="2,2")
  addProblem(folder="hc2-dryrun-hard",               probid="C_dry3",   depends=True,  color="indigo", runtime=1, special_runtime="2,2")
