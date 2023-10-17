import unittest
from sqlinterp import conditions as cond


class TestComparisonConditions(unittest.TestCase):
    def test_equal(self):
        equal_condition = cond.Equal(42)
        self.assertTrue(equal_condition.check(42))  # Should be equal
        self.assertFalse(equal_condition.check(24))  # Should not be equal

    def test_not_equal(self):
        not_equal_condition = cond.NotEqual(42)
        self.assertTrue(not_equal_condition.check(24))  # Should not be equal
        self.assertFalse(not_equal_condition.check(42))  # Should be equal

    def test_greater_than(self):
        gt_condition = cond.GreaterThan(42)
        self.assertTrue(gt_condition.check(43))  # 43 > 42
        self.assertFalse(gt_condition.check(42))  # 42 is not greater than 42
        self.assertFalse(gt_condition.check(41))  # 41 is not greater than 42

    def test_greater_than_or_equal_to(self):
        gte_condition = cond.GreaterThanOrEqualTo(42)
        self.assertTrue(gte_condition.check(43))  # 43 >= 42
        self.assertTrue(gte_condition.check(42))  # 42 >= 42
        # 41 is not greater than or equal to 42
        self.assertFalse(gte_condition.check(41))

    def test_less_than(self):
        lt_condition = cond.LessThan(42)
        self.assertTrue(lt_condition.check(41))  # 41 < 42
        self.assertFalse(lt_condition.check(42))  # 42 is not less than 42
        self.assertFalse(lt_condition.check(43))  # 43 is not less than 42

    def test_less_than_or_equal_to(self):
        lte_condition = cond.LessThanOrEqualTo(42)
        self.assertTrue(lte_condition.check(41))  # 41 <= 42
        self.assertTrue(lte_condition.check(42))  # 42 <= 42
        # 43 is not less than or equal to 42
        self.assertFalse(lte_condition.check(43))


if __name__ == '__main__':
    unittest.main()
