# Configuration file for polygon2domjudge
# Local/selection contest 2015

setPolygonContestId(3755)  # Needed to find the correct package file
setDomjudgeContestId(5)
addLanguage("english")     # Call this method for every language you have statements in, and before calling add problem
#addLanguage("french")

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
addProblem(folder="goodbye-palindrome",      probid="A", color="red")
addProblem(folder="saucer-refueling",        probid="B", color="orange")
addProblem(folder="water-on-mars",           probid="C", color="green")
addProblem(folder="max-factor",              probid="D", color="midnightblue")
addProblem(folder="2sum",                    probid="E", color="blue")
addProblem(folder="labelling-saucers",       probid="F", color="ivory")
addProblem(folder="counting-paths",          probid="G", color="gold")
