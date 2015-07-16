function dist_g = dist_g(X,Y)

dist_g = norm(logm(X) - logm(Y),'fro');

