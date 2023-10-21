import unittest
from sqlinterp import conditions as cond
from sqlinterp.conditions import And, Or, Not
from utility import console


class TestComparisonConditions(unittest.TestCase):
    def test_and_operator(self):
        and_condition = cond.And(
            cond.GreaterThan("column1", -100),
            cond.LessThan("column1", 100))

        # Both conditions are true
        self.assertTrue(and_condition.check(16))
        self.assertTrue(and_condition.check(25))
        self.assertTrue(and_condition.check(-25))
        self.assertTrue(and_condition.check(-99))
        self.assertTrue(and_condition.check(85))

        # Second condition is false
        self.assertFalse(and_condition.check(100))
        self.assertFalse(and_condition.check(-100))
        self.assertFalse(and_condition.check(101))
        self.assertFalse(and_condition.check(108458))
        self.assertFalse(and_condition.check(-108458))

    def test_or_operator(self):
        or_condition = cond.Or(
            cond.Equal("column1", 42),
            cond.Equal("column1", 86))

        # First condition is true
        self.assertTrue(or_condition.check(42))
        self.assertTrue(or_condition.check(86))
        # Second condition is true
        self.assertFalse(or_condition.check(85))

    def test_not_operator(self):
        not_condition = cond.Not(cond.Equal("column1", 42))
        # Inverted condition is true
        self.assertTrue(not_condition.check(24))
        # Inverted condition is false
        self.assertFalse(not_condition.check(42))


if __name__ == '__main__':
    unittest.main()
