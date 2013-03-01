def setUpModule():
    print "setUpModule"
def tearDownModule():
    print "tearDownModule"

import random
import unittest

class TestSequenceFunctions(unittest.TestCase):
    @classmethod
    def setUpClass( self ):
        print "setUpClass"
    @classmethod
    def tearDownClass( self ):
        print "tearDownClass"

    def setUp(self):
        print "setUp"
        self.seq = range(10)
    def tearDown( self ):
        print "tearDown"

    def test_shuffle(self):
        print "test"
        # make sure the shuffled sequence does not lose any elements
        random.shuffle(self.seq)
        self.seq.sort()
        self.assertEqual(self.seq, range(10))

        # should raise an exception for an immutable sequence
        self.assertRaises(TypeError, random.shuffle, (1,2,3))

    def test_choice(self):
        print "test"
        element = random.choice(self.seq)
        self.assertTrue(element in self.seq)

    def test_sample(self):
        print "test"
        with self.assertRaises(ValueError):
            random.sample(self.seq, 20)
        for element in random.sample(self.seq, 5):
            self.assertTrue(element in self.seq)

if __name__ == '__main__':
    unittest.main()
