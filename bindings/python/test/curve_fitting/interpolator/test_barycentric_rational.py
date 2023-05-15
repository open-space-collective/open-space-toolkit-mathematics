# Apache License 2.0

from ostk.mathematics.curve_fitting.interpolator import BarycentricRational


class TestBarycentricRational:
    def test_default_constructor(self):
        BarycentricRational(
            x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
        )

    def test_evaluate(self):
        spline = BarycentricRational(
            x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
        )

        assert spline.evaluate(0.0) == 0.0
        assert spline.evaluate(1.0) == 3.0
        assert spline.evaluate(2.0) == 6.0
        assert spline.evaluate(4.0) == 9.0
        assert spline.evaluate(5.0) == 17.0
        assert spline.evaluate(6.0) == 5.0

        assert (
            spline.evaluate(x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0])
            == [0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
        ).all()
