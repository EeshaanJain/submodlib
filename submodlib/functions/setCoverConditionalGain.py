# setCoverConditionalGain.py
# Author: Vishal Kaushal <vishal.kaushal@gmail.com>
from .setFunction import SetFunction
from submodlib_cpp import SetCoverConditionalGain

class SetCoverConditionalGainFunction(SetFunction):
	"""Implementation of the Set Cover Conditional Gain (SCCG) function.

	Given a :ref:`functions.conditional-gain` function, Set Cover Conditional Gain function is its instantiation using a :class:`~submodlib.functions.setCover.SetCoverFunction`. Mathematically, it takes the following form:

	.. math::
			f(A | P) = w(\\gamma(A) \\setminus \\gamma(P))
	
	Parameters
	----------

	n : int
		Number of elements in the ground set. Must be > 0.
	
	cover_set : list
		List of sets. Each set is the set of concepts covered by the corresponding data point / image. Hence cover_set is of size n.
	
	num_concepts : int
		Number of concepts.
	
	private_concepts : set
		Set of private concepts. That is, the concepts which should not be covered in the optimal subset.
	
	concept_weights : list
		Weight :math:`w_i` of each concept. Size must be same as num_concepts.
	
	"""

	def __init__(self, n, cover_set, num_concepts, private_concepts, concept_weights=None):
		self.n = n
		self.cover_set = cover_set
		self.num_concepts = num_concepts
		self.private_concepts = private_concepts
		self.concept_weights = concept_weights
		self.cpp_obj = None

		if self.n <= 0:
			raise Exception("ERROR: Number of elements in ground set must be positive")

		if self.n != len(self.cover_set):
			raise Exception("ERROR: Mismtach between n and len(cover_set)")
		
		if (type(self.concept_weights) != type(None)):
			if self.num_concepts != len(self.concept_weights):
			    raise Exception("ERROR: Mismtach between num_conepts and len(concept_weights)")
		else:
			self.concept_weights = [1] * self.num_concepts

		self.cpp_obj = SetCoverConditionalGain(self.n, self.cover_set, self.num_concepts, self.concept_weights, self.private_concepts)

		self.effective_ground = set(range(n))

	