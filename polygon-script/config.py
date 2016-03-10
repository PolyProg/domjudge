# Configuration file for polygon2domjudge
# Local/selection contest 2015

setPolygonContestId(3835)  # Needed to find the correct package file
setDomjudgeContestId(7)
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

# Import all files to contestant package that contain this string
contestantDataTag("contestant_package")
# Don't add realInput.in to contestant package for offline tasks
suppressRealInputForOffline(True)

# Dry run
addProblem(folder="hc2-2016-dryrun-easy",       probid="X_dry1",   depends=False,     runtime=1 , special_runtime="1,1",   color="lavender")
addProblem(folder="hc2-2016-dryrun-medium",     probid="Y_dry2",   depends=True,      runtime=1 , special_runtime="1,1",   color="mediumpurple")
addProblem(folder="hc2-2016-dryrun-hard",       probid="Z_dry3",   depends=True,      runtime=1 , special_runtime="1,1",   color="indigo")

# Main contest
setPolygonContestId(3767)
setDomjudgeContestId(8)

addProblem(folder="collective-mindsets-easy",   probid="A_mind1",  depends=False,     runtime=1 , special_runtime="1,1",   color="lemonchiffon")
addProblem(folder="collective-mindsets-medium", probid="B_mind2",  depends=True,      runtime=1 , special_runtime="1,1",   color="yellow")
addProblem(folder="collective-mindsets-hard",   probid="C_mind3",  depends="A_mind1", runtime=10, special_runtime="15,30", color="goldenrod", compare="mind3")

addProblem(folder="recover-polygon-easy",       probid="D_poly1",  depends=False,     runtime=2 , special_runtime="3,6",   color="lightblue")
addProblem(folder="recover-polygon-medium",     probid="E_poly2",  depends=True,      runtime=2 , special_runtime="3,6",   color="skyblue")
addProblem(folder="recover-polygon-hard",       probid="F_poly3",  depends=True,      runtime=2 , special_runtime="3,6",   color="deepskyblue")

addProblem(folder="tree-diam-easy",             probid="G_tree1",  depends=False,     runtime=2 , special_runtime="3,6",   color="whitesmoke")
addProblem(folder="tree-diam-medium",           probid="H_tree2",  depends=True,      runtime=2 , special_runtime="3,6",   color="gainsboro")
addProblem(folder="tree-diam-hard",             probid="I_tree3",  depends=True,      runtime=2 , special_runtime="3,6",   color="silver")

addProblem(folder="hc2-2016-walls-easy",        probid="J_wall1",  depends=False,     runtime=1 , special_runtime="1,1",   color="palegreen")
addProblem(folder="hc2-2016-walls-medium",      probid="K_wall2",  depends=True,      runtime=15, special_runtime="22,45", color="limegreen")
addProblem(folder="hc2-2016-walls-hard",        probid="L_wall3",  depends=True,      runtime=2 , special_runtime="3,6",   color="green")

addProblem(folder="jigsaw-puzzle-easy",         probid="M_jiggy1", depends=False,     runtime=15, special_runtime="22,45", color="lightcoral", offline="tests/1", compare="jiggy1")
addProblem(folder="jigsaw-puzzle-medium",       probid="N_jiggy2", depends=True,      runtime=15, special_runtime="22,45", color="red",        offline="tests/1", compare="jiggy2")

addProblem(folder="connect-the-dots-medium",    probid="O_dots2",   depends=False,    runtime=3 , special_runtime="4,6",   color="orange", compare="dots2")
addProblem(folder="connect-the-dots-hard",      probid="P_dots3",   depends=True,     runtime=8 , special_runtime="12,16", color="darkorange", compare="dots3")

