#!/usr/bin/env python

import re
import logging
import os
import json
import xml.etree.ElementTree as ET
import string
import zipfile
import StringIO

contDataTag = None

class Problem:
  def __init__(self, folder, probid, domjudgeContestId, polygonContestPath, dependency, htmlcolor, compare, run, offline, runtime, special_runtime):
    self.folder = folder
    self.probid = probid
    self.domjudgeContestId = domjudgeContestId
    self.polygonContestPath = polygonContestPath
    self.dependency = dependency
    self.htmlcolor = htmlcolor
    self.compare = compare
    self.run = run
    self.offline = offline
    self.runtime = str(runtime)
    self.special_runtime = special_runtime
    self.testsets = list()

    jsonfilename = polygonContestPath + "/problems/" + folder + "/statements/english/problem-properties.json"
    j = json.load(open(jsonfilename, 'r'))
    self.name = j["name"]
    if self.runtime == "0":
      self.runtime = str(int(j["timeLimit"])/1000)

    self.sampleio = list()
    problemxml = polygonContestPath + "/problems/" + folder + "/problem.xml"
    tree = ET.parse(problemxml)
    root = tree.getroot()
    self.ntests = 0
    for testset in root.iter('testset'):
      if "name" in testset.attrib:
        self.nteststs = 0
        testsetname = testset.attrib["name"]
        self.testsets.append(testsetname)
        for test in testset.iter('test'):
          if "method" in test.attrib:
            self.ntests += 1
            self.nteststs += 1
            if ("sample" in test.attrib) and test.attrib["sample"] == "true":
              self.sampleio.append(testsetname+"/"+str(self.nteststs))

    if self.compare == "":
      for checker in root.iter('checker'):
        if "name" in checker.attrib:
          self.compare = checker.attrib["name"][5:-4]


  def __str__(self):
    return "Problem %-30s (%-8s) depends: %-8s color: %s time: %-2s run: %-8s cmp: %-8s tests: %3d sample: %s" % (
      self.name[0:30], self.probid, self.dependency, self.htmlcolor, self.runtime,
      self.run, self.compare, self.ntests, str(self.sampleio)
      )

  def compileLatex(self, languages):
    if len(languages) == 0:
      raise BaseException("Need at least one language to add problems, please call addLanguage")
    for lang in languages:
      latexfolder = self.polygonContestPath + "/problems/" + self.folder + "/statements/"+lang
      latexfile = "statement"
      latexpath = latexfolder+"/"+latexfile+".tex"
      os.system("cp latex-head.tex "+latexpath)
      os.system("cp "+self.polygonContestPath+"/statements/"+lang+"/*.sty "+latexfolder)
      # Update problem ID in sty file (yes, this is a hack :-) )
      safeprobid = self.probid.replace("_", "\\\\_")
      os.system("sed -i 's/.*textbf.*arabic.problem.*/\\\\textbf{\\\\problemheadfont\\\\textsf{\\\\kw@Problem\\\\ "+safeprobid+".\\\\ #1}}%/' "+latexfolder+"/olymp.sty")
      os.system("sed -i 's/\\\\vbox/\\\\providecommand{\\\\ignorethis}[1]{}\\\\ignorethis/' "+latexfolder+"/olymp.sty")
      os.system("echo '\\input problem.tex' >> "+latexpath)
      os.system("echo '\\end{document}' >> "+latexpath)
      os.system("(cd "+latexfolder+" ;" +
                " latex "+latexfile+".tex ;"+
                " latex "+latexfile+".tex ;"+
                " dvips "+latexfile+".dvi ;"+
                " dvipdfmx -p a4 "+latexfile+".dvi ;"+
                " mv "+latexfile+".pdf problem.pdf ;"+
                " rm -f *.log *.aux *.dvi *.ps)")

  def package(self, args, languages):
    ok = True
    zipf = zipfile.ZipFile("djConfig/" + self.probid + ".zip", "w", zipfile.ZIP_DEFLATED)
    ok = self.makeConfigurationFile(zipf) and ok
    ok = self.addStatement(zipf, languages) and ok
    ok = self.addContestant(zipf) and ok
    ok = self.addIO(zipf) and ok
    if args.solutions:
      ok = self.addSolutions(zipf) and ok
    zipf.close()
    if args.checkers and self.compare != "":
      checkersource = self.polygonContestPath + "/problems/" + self.folder + "/check.cpp"
      os.system("cp " + checkersource + " ../judge/" + self.compare + "_checker.cpp")
    if args.checkers and self.run != "":
      checkersource = self.polygonContestPath + "/problems/" + self.folder + "/files/runjury_"+self.run+".cpp"
      os.system("cp " + checkersource + " ../judge/runjury_" + self.run + ".cpp")
      
    if not ok:
      print "!!! PROBLEM NOT OK"

    return ok

  def addStatement(self, zipf, languages):
    statementsfolder = self.polygonContestPath + "/problems/" + self.folder + "/statements"
    pdftk = "pdftk "
    for lang in languages:
      pdftk += lang+"/problem.pdf "
    pdftk += "cat output problem.pdf"
    os.system("(cd "+statementsfolder+";" + pdftk + ")");
    statement = statementsfolder+"/problem.pdf"
    zipf.write(statement, "problem.pdf")
    return True

  def addContestant(self, zipf):
    global contDataTag 
    tempfile = StringIO.StringIO()
    contzip = zipfile.ZipFile(tempfile, "w", zipfile.ZIP_DEFLATED)

    count = 0
    for testset in self.testsets:
      testsfolder = self.polygonContestPath + "/problems/" + self.folder + "/" + testset
      for entry in os.listdir(testsfolder):
        base, ext = os.path.splitext(testsfolder + "/" + entry)
        logging.debug(entry + " --- " + base + " --- " + ext)
        if os.path.isfile(testsfolder + "/" + entry) and ext == ".a":
          testid = entry[:2]
          if testset+"/"+str(int(testid)) in self.sampleio:
            contzip.write(testsfolder+"/"+entry, testset+testid+".out")
            if os.path.isfile(testsfolder + "/" + testid):
              contzip.write(testsfolder+"/"+testid, testset+testid+".in")
              count += 1
          if testset+"/"+str(int(testid)) == self.offline:
            if os.path.isfile(testsfolder + "/" + testid):
              contzip.write(testsfolder+"/"+testid, "realInput.in")
              count += 1
    if count == 0:
      contzip.writestr("no-sample-testcases.txt", "This problem has no sample testcases.")

    testsfolder = self.polygonContestPath + "/problems/" + self.folder + "/files"
    for entry in os.listdir(testsfolder):
      base, ext = os.path.splitext(testsfolder + "/" + entry)
      if os.path.isfile(testsfolder + "/" + entry) and (contDataTag is not None and entry.find(contDataTag) != -1):
        if ext != ".zip":
          contzip.write(testsfolder+"/"+entry, entry)
        else:
          with zipfile.ZipFile(testsfolder+"/"+entry, "r") as z:
            for name in z.namelist():
              contzip.writestr(name, z.read(name))


    contzip.close()
    zipf.writestr("data.zip", tempfile.getvalue())
    tempfile.close()
    if self.offline is not None:
        return count-1 == len(self.sampleio)
    else:
        return count == len(self.sampleio)

  def addIO(self, zipf):
    count = 0
    for testset in self.testsets:
      testsfolder = self.polygonContestPath + "/problems/" + self.folder + "/" + testset
      for entry in os.listdir(testsfolder):
        base, ext = os.path.splitext(testsfolder + "/" + entry)
        logging.debug(entry + " --- " + base + " --- " + ext)
        if os.path.isfile(testsfolder + "/" + entry) and ext == ".a":
          testid = entry[:-2]
          if (self.offline is None) or testset+"/"+str(int(testid)) == self.offline:
            zipf.write(testsfolder+"/"+entry, testset+testid+".out")
            if os.path.isfile(testsfolder + "/" + testid):
              zipf.write(testsfolder+"/"+testid, testset+testid+".in")
              count += 1
    return count == self.ntests or ((self.offline is not None) and count == 1)

  def addSolutions(self, zipf):
    count = 0
    testsfolder = self.polygonContestPath + "/problems/" + self.folder + "/solutions"
    for entry in os.listdir(testsfolder):
      base, ext = os.path.splitext(testsfolder + "/" + entry)
      logging.debug(entry + " --- " + base + " --- " + ext)
      if os.path.isfile(testsfolder + "/" + entry) and ext in [".cpp", ".java", ".scala", ".c", ".c98", ".py", ".py2", ".py3", ".rb"]:
        zipf.write(testsfolder+"/"+entry, entry)
    testsfolder = self.polygonContestPath + "/problems/" + self.folder + "/files"
    for entry in os.listdir(testsfolder):
      base, ext = os.path.splitext(testsfolder + "/" + entry)
      logging.debug(entry + " --- " + base + " --- " + ext)
      if os.path.isfile(testsfolder + "/" + entry) and ext in [".cpp", ".java", ".scala", ".c", ".c98", ".py", ".py2", ".py3", ".rb"]:
        if "DOMJUDGESOLUTION" in entry:
          zipf.write(testsfolder+"/"+entry, entry)
    return True

  def makeConfigurationFile(self, zipf):
    config = "";
    config += "name = \""+self.name+"\"\n"
    config += "timelimit = "+self.runtime+"\n"
    config += "color = "+self.htmlcolor.upper()+"\n"
    config += "probid = " + self.probid + "\n"
    config += "cid = " + self.domjudgeContestId + "\n"
    config += "allow_submit = 1\n"
    config += "allow_judge = 1\n"
    if self.dependency is not None and self.dependency != "":
      config += "depends = " + self.dependency + "\n"
    if self.run is not None and self.run != "":
      config += "special_run = " + self.run + "\n"
    if self.special_runtime is not None and self.special_runtime != "":
      config += "special_runtime = " + self.special_runtime + "\n"
    if self.compare is not None and self.compare != "":
      config += "special_compare = " + self.compare + "\n"
    zipf.writestr("domjudge-problem.ini", config)
    return True
    
