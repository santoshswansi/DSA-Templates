  Edge edges[]={{0,1},{1,2},{2,0},{2,1},{3,2},{4,5},{5,4}};
  int noVertices=6;
  int noEdges=sizeof(edges)/sizeof(edges[0]); 

  Graph graph(edges,noEdges,noVertices); //construct graph
