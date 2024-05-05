1 Explcit Smoothing (David Baier):
Iterated over each vertice for the uniform laplace and then used the vertexvertex iterator to compute the difference between all neighboring vertices. summed up the weight of 1 to then divide the laplacian by the sum.
For the cotan laplacian, iterated over each vertex and then used the vertexhalfedged iterator to iterate over all halfedges going to the neighboring vertex. This was done to get the edge between the to points and used the edege_weight property to get the cotan value. 
summed all contan weights with the loop and then divided the laplacian by this value.


3 Feature Enhancement:

Bad & Nice Max:
    The mesh of bad max is has not uniformly defined faces and neither an adaptive mesh, therefore the differences between neighboring vertices get enhanced with different strengths. With the nice Max mesh, the length between vertices are more normalized, and there the coefficient weights the different differences more equally.
    y

First interesting image: Enhanced lips of nice Max (enhacned_lips_max.png): 
    1x (10 iterations of uniform smoothing)
    2x (10 iter cotan smoothing Enhancement coefficient(3.00))
    1x (5 iterations of uniform Smoothing)

    The first 10 iterations smoothed the surface and let the triangles(faces) become more similar. With the more similar faces, the 2x 10 iterations exxaragated the prominent features(here the lips), the unsimilarities led then to some spikes,
    which then get flattened with the last 5 iterations of the uniform smoothing. 

    From the signal processing view, we flattened the noise in the signal within the first smoothing (but also some normalization takes place), after that we enhanced the signal peaks, by adding the differences to the originally smoothed signal. This leads to additional noisy peaks,which are then further flattened by the last smooth function. 

Second interesting image: Needle Face (needle_face_max.png):
    1x (10 iterations Cotan laplacian Smoothing)
    4x (10 iterations Uniform laplacian Feature enhancement (2.00))
    5x (10 iterations Cotan laplacian Smoothing)

    With the cotan smoothing we do not change the figure of the triangle(face), therefore pointy features get more prominent when smoothed. The uniform enhancement then makes the faces more similar, which smoothes the surrounding area, but enhances the peaks. The last smoothing then enhances the peaks more, but smoothes the already flat areas.

    In the signal processing view a flattening of the signal (here the mesh) takes place, but not really a normalization, therefore specific peaks still are there. With the uniform enhancement, the signal gets normalized and the difference between the input and output signal is then added to the input signal. The last step then again smoothens the signal.

Third interesting image: Checker Bunny (checker_bunny.png)
    3 x (15 iterations Cotan laplacian Smoothing)
    1 x (10 iterations Uniform laplacian Smoothing)
    5 x (10 iterations Uniform laplacian Feature enhancement (2.00))

    The first 3 smoothing enable the edges (specifically from the ear, and somehow for some checker like patterns(not really visible in this state.)) The one uniform smoothing then normalizes the faces, which then enables the first defined patterns to enhance and start to grow out of the normal mesh.

    Signal processing: Firt a smoothing of the signal witout normalization, afterwards, it gets smoothed and normalized. This then gives then the repetitive pattern, which then get enhanced.