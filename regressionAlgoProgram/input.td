class RegressionProblem {
  string RegressionType;
  list<list<int>> DataPoints;
}

def Example1 : RegressionProblem {
  let RegressionType = "linear";
  let DataPoints = [[1,2],[2,3],[3,5],[4,7]];
}