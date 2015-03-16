
# Main contest
setPolygonContestId(2302)
setDomjudgeContestId(2)
addProblem(folder="fantastic-four-1",              probid="A_fant0",  depends=False, color="lightyellow", offline=3)
addProblem(folder="fantastic-four-2",              probid="B_fant1",  depends=False, color="lemonchiffon", run="fanfour2")
addProblem(folder="fantastic-four-3",              probid="C_fant2",  depends=True,  color="yellow",       run="fanfour3")
addProblem(folder="fantastic-four-4",              probid="D_fant3",  depends=True,  color="goldenrod",    run="fanfour4")

addProblem(folder="hc2-planet-destruction-easy",   probid="E_pland1", depends=False, color="lightblue")
addProblem(folder="hc2-planet-destruction-med",    probid="F_pland2", depends=True,  color="skyblue")
addProblem(folder="hc2-planet-destruction-hard",   probid="G_pland3", depends=True,  color="deepskyblue")

addProblem(folder="synchronizing-automata-easy",   probid="H_hgath1", depends=False, color="whitesmoke")
addProblem(folder="synchronizing-automata-medium", probid="I_hgath2", depends=True,  color="gainsboro")
addProblem(folder="synchronizing-automata-hard",   probid="J_hgath3", depends=True,  color="silver",       compare="sync3")

addProblem(folder="recognize-shape-easy",          probid="K_shape1", depends=False, color="palegreen")
addProblem(folder="recognize-shape-medium",        probid="L_shape2", depends=True,  color="limegreen")
addProblem(folder="recognize-shape-hard",          probid="M_shape3", depends=True,  color="green")

addProblem(folder="counting-numbers-easy",         probid="N_shiel1", depends=False, color="lightcoral")
addProblem(folder="counting-numbers-medium",       probid="O_shiel2", depends=True,  color="red")
addProblem(folder="counting-numbers-hard",         probid="P_shiel3", depends=True,  color="darkred")

# Dry run
setPolygonContestId(2441)
# setDomjudgeContestId(3)
addProblem(folder="hc2-dryrun-easy",               probid="A_dry1",   depends=False, color="lavender")
addProblem(folder="hc2-dryrun-medium",             probid="B_dry2",   depends=True,  color="mediumpurple")
addProblem(folder="hc2-dryrun-hard",               probid="C_dry3",   depends=True,  color="indigo")
