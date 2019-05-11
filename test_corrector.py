import unittest
from corrector import *

class TestSum(unittest.TestCase):

	def test_number_of_editions(self, wrong, corrected, num_changes):
		num = number_of_editions(wrong, corrected)
		self.assertEqual(num, num_changes, "Should be " + str(num_changes))

	def test(self):
		self.test_number_of_editions("", "", 0)
		self.test_number_of_editions("a", "", 1)
		self.test_number_of_editions("a", "b", 1)

	def test2(self):
		self.test_number_of_editions("hao", "eao", 1)

	def test3(self):
		word = buscar_paraula_correcta("hao", ['eao', 'ao', 'kl'])
		self.assertEqual(word, 'eao', 'Should be eao')