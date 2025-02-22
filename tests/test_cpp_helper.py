import pytest
import numpy as np
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.metrics.pairwise import cosine_similarity
from sklearn.metrics.pairwise import cosine_distances
from sklearn.neighbors import NearestNeighbors
from scipy import sparse
import scipy
import submodlib_cpp as subcp
from submodlib.helper import create_kernel


list_tests=[
    np.array([[0, 1, 3], [5, 1, 5], [10, 2, 6], [12,20,68]]),
    np.array([[1, 1, 1]]),
    np.array([ [1], [1], [1] ]),
    np.zeros((2,2)),
    np.ones((3,2)),
    np.identity(5),
]


list_tests_neigh=[
    np.array([[0, 1, 3, 5], [5, 1, 5, -6], [10, 2, 6, -8], [12,20,68, 200], [12,20,68, 200]]),
    np.array([[0, 1, 3], [5, 1, 5], [10, 2, 6], [12,20,68]]),
    np.array([[100, 21, 365, 5], [57, 18, -5, -6], [16, 255, 68, -8], [2,20,6, 2000], [12,20,68, 200]])
]


list_val1_ES=[
    np.array([
 [1.00000000e+00, 0, 0, 0, 0],
 [0, 1.00000000e+00, 0, 0, 0],
 [0, 0, 1.00000000e+00, 0, 0],
 [0, 0, 0, 1.00000000e+00, 0],
 [0, 0, 0, 1.00000000e+00, 0]]),
    np.array([
 [1.00000000e+00, 0, 0, 0],
 [0, 1.00000000e+00, 0, 0],
 [0, 0, 1.00000000e+00, 0],
 [0, 0, 0, 1.00000000e+00],]),
    np.array([
 [1.00000000e+000, 0, 0, 0, 0],
 [0, 1.00000000e+000, 0, 0, 0],
 [0, 0, 1.00000000e+000, 0, 0],
 [0, 0, 0, 1.00000000e+000, 0],
 [0, 0, 0, 0, 1.00000000e+000],])
]


list_val2_ES=[
    np.array([
 [1.00000000e+00, 4.68004632e-02, 0, 0, 0],
 [0, 1.00000000e+00, 2.48592296e-01, 0, 0],
 [0, 2.48592296e-01, 1.00000000e+00, 0, 0],
 [0, 0, 0, 1.00000000e+00, 1.00000000e+00],
 [0, 0, 0, 1.00000000e+00, 1.00000000e+00]]),
    np.array([
 [1.00000000e+00, 1.66118326e-01, 0, 0],
 [0, 1.00000000e+00, 1.76921206e-01, 0],
 [0, 1.76921206e-01, 1.00000000e+00, 0],
 [0, 0, 4.46161399e-10, 1.00000000e+00],]),
    np.array([
 [1.00000000e+000, 0, 0, 0, 1.81402633e-040],
 [0, 1.00000000e+000, 0, 0, 5.91921741e-025],
 [0, 5.11312375e-028, 1.00000000e+000, 0, 0],
 [0, 0, 0, 1.00000000e+000, 2.80912385e-196],
 [0, 5.91921741e-025, 0, 0, 1.00000000e+000],])
]

list_val3_ES=[
    np.array([
 [1.00000000e+00, 4.68004632e-02, 1.53625389e-02, 0, 0],
 [4.68004632e-02, 1.00000000e+00, 2.48592296e-01, 0, 0],
 [1.53625389e-02, 2.48592296e-01, 1.00000000e+00, 0, 0],
 [3.54753001e-23, 0, 0, 1.00000000e+00, 1.00000000e+00],
 [3.54753001e-23, 0, 0, 1.00000000e+00, 1.00000000e+00]]),
    np.array([
 [1.00000000e+00, 1.66118326e-01, 3.03175207e-02, 0],
 [1.66118326e-01, 1.00000000e+00, 1.76921206e-01, 0],
 [3.03175207e-02, 1.76921206e-01, 1.00000000e+00, 0],
 [0, 2.63226999e-10, 4.46161399e-10, 1.00000000e+00],]),
    np.array([
 [1.00000000e+000, 3.45494536e-041, 0, 0, 1.81402633e-040],
 [0, 1.00000000e+000, 5.11312375e-028, 0, 5.91921741e-025],
 [0, 5.11312375e-028, 1.00000000e+000, 0, 8.38725031e-035],
 [0, 1.30643562e-218, 0, 1.00000000e+000, 2.80912385e-196],
 [0, 5.91921741e-025, 8.38725031e-035, 0, 1.00000000e+000],])
]


list_val1_CS=[
    np.array([
 [ 1.        , 0, 0,  0,  0],
 [0,  1.        ,  0, 0, 0],
 [0,  0,  1.        , 0, 0],
 [ 0, 0, 0,  1.        ,  0        ],
 [ 0, 0, 0,  1.        ,  0        ],]),
    np.array([
 [1.        , 0, 0, 0],
 [0, 1.        , 0, 0],
 [0, 0, 1.        , 0 ],
 [0, 0, 0 , 1.        ],]),
    np.array([
 [ 1.        ,  0,  0,  0,  0],
 [ 0,  1.        ,  0, 0, 0],
 [ 0,  0,  1.        , 0,  0],
 [ 0, 0, 0,  1.        ,  0],
 [ 0, 0,  0,  0,  1.        ],])
]

list_val2_CS=[
    np.array([
 [ 1.        , 0, 0,  0.97349105,  0],
 [0,  1.        ,  0.97581759, 0, 0],
 [0,  0.97581759,  1.        , 0, 0],
 [ 0, 0, 0,  1.        ,  1.        ],
 [ 0, 0, 0,  1.        ,  1.        ],]),
    np.array([
 [1.        , 0, 0, 0.98534148],
 [0, 1.        , 0.97043119, 0],
 [0, 0.97043119, 1.        , 0 ],
 [0.98534148, 0, 0 , 1.        ],]),
    np.array([
 [ 1.        ,  0,  0,  0,  0.34060725],
 [ 0,  1.        ,  0.32673257, 0, 0],
 [ 0,  0.32673257,  1.        , 0,  0],
 [ 0, 0, 0,  1.        ,  0.94295957],
 [ 0, 0,  0,  0.94295957,  1.        ],])
]

list_val3_CS=[
    np.array([
 [ 1.        , 0, 0,  0.97349105,  0.97349105],
 [-0.25370813,  1.        ,  0.97581759, 0, 0],
 [-0.23669053,  0.97581759,  1.        , 0, 0],
 [ 0.97349105, 0, 0,  1.        ,  1.        ],
 [ 0.97349105, 0, 0,  1.        ,  1.        ],]),
    np.array([
 [1.        , 0.70849191, 0, 0.98534148],
 [0, 1.        , 0.97043119, 0.81809351],
 [0, 0.97043119, 1.        , 0.6677641 ],
 [0.98534148, 0.81809351, 0 , 1.        ],]),
    np.array([
 [ 1.        ,  0,  0.31649794,  0,  0.34060725],
 [ 0.18480505,  1.        ,  0.32673257, 0, 0],
 [ 0.31649794,  0.32673257,  1.        , 0,  0],
 [ 0.01689587, 0, 0,  1.        ,  0.94295957],
 [ 0.34060725, 0,  0,  0.94295957,  1.        ],])
]

l_ES1 = list(zip(list_tests_neigh, list_val1_ES))
l_CS1 = list(zip(list_tests_neigh, list_val1_CS))

l_ES2 = list(zip(list_tests_neigh, list_val2_ES))
l_CS2 = list(zip(list_tests_neigh, list_val2_CS))

l_ES3 = list(zip(list_tests_neigh, list_val3_ES))
l_CS3 = list(zip(list_tests_neigh, list_val3_CS))





class TestHelper:
    
    @pytest.mark.parametrize("data", list_tests)
    def test_euclidean_full(self, data):
        ED = euclidean_distances(data) 
        gamma = 1/np.shape(data)[1] 
        ES = np.exp(-ED* gamma) #sklearn ground truth 
        num_neigh=np.shape(data)[0]
        c = subcp.create_kernel(data.tolist(),'euclidean',num_neigh)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, ES)
    
    @pytest.mark.parametrize("data", list_tests)
    def test_cosine_full(self, data):
        CS = cosine_similarity(data)  #sklearn ground truth 
        num_neigh=np.shape(data)[0]
        c = subcp.create_kernel(data.tolist(),'cosine',num_neigh)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, CS)


    @pytest.mark.parametrize("data, val", l_ES1)
    def test_euclidean_neigh1(self, data, val):
        c = subcp.create_kernel(data.tolist(),'euclidean',1)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)

    @pytest.mark.parametrize("data, val", l_CS1)
    def test_cosine_neigh1(self, data, val):
        c = subcp.create_kernel(data.tolist(),'cosine',1)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)


    @pytest.mark.parametrize("data, val", l_ES2)
    def test_euclidean_neigh2(self, data, val):
        c = subcp.create_kernel(data.tolist(),'euclidean',2)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)

    @pytest.mark.parametrize("data, val", l_CS2)
    def test_cosine_neigh2(self, data, val):
        c = subcp.create_kernel(data.tolist(),'cosine',2)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)

    @pytest.mark.parametrize("data, val", l_ES3)
    def test_euclidean_neigh3(self, data, val):
        c = subcp.create_kernel(data.tolist(),'euclidean',3)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)

    @pytest.mark.parametrize("data, val", l_CS3)
    def test_cosine_neigh3(self, data, val):
        c = subcp.create_kernel(data.tolist(),'cosine',3)
        value = c[0]
        row = list(map(lambda arg: int(arg), c[1]))
        col = list(map(lambda arg: int(arg), c[2]))
        s = np.zeros((np.shape(data)[0],np.shape(data)[0]))
        s[row, col] = value
        assert np.allclose(s, val)

      