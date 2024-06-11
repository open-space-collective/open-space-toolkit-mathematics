# Apache License 2.0

"""
Generate reference data for the Euler angle representation of rotations.
"""

import math

import pandas as pd

from scipy.spatial.transform import Rotation

axis_sequences = [
    "XYZ",
    "ZXY",
    "ZYX",
]

count = 1000


def sanitize_euler_angle(args):
    # https://math.stackexchange.com/a/55552
    phi, theta, psi = args

    if phi < 0.0:
        phi = phi + math.pi
        theta = math.pi - theta
        psi = psi + math.pi

    return [phi, theta, psi]


for axis_sequence in axis_sequences:
    rotations = [
        Rotation.identity(),
        *Rotation.random(count),
    ]

    euler_angles = [
        sanitize_euler_angle(list(rotation.as_euler(axis_sequence)))
        for rotation in rotations
    ]

    pd.DataFrame(
        [
            list(rotation.as_quat()) + euler_angle
            for rotation, euler_angle in zip(rotations, euler_angles)
        ],
        columns=[
            "q_x",
            "q_y",
            "q_z",
            "q_s",
            "phi",
            "theta",
            "psi",
        ],
    ).to_csv(
        f"Quaternion-EulerAngle-{axis_sequence}.csv",
        index=False,
    )

    pd.DataFrame(
        [
            list(rotation.as_rotvec()) + euler_angle
            for rotation, euler_angle in zip(rotations, euler_angles)
        ],
        columns=[
            "rotvec_x",
            "rotvec_y",
            "rotvec_z",
            "phi",
            "theta",
            "psi",
        ],
    ).to_csv(
        f"RotationVector-EulerAngle-{axis_sequence}.csv",
        index=False,
    )

    pd.DataFrame(
        [
            list(rotation.as_matrix().transpose().reshape(9)) + euler_angle
            for rotation, euler_angle in zip(rotations, euler_angles)
        ],
        columns=[
            "m_xx",
            "m_xy",
            "m_xz",
            "m_yx",
            "m_yy",
            "m_yz",
            "m_zx",
            "m_zy",
            "m_zz",
            "phi",
            "theta",
            "psi",
        ],
    ).to_csv(
        f"RotationMatrix-EulerAngle-{axis_sequence}.csv",
        index=False,
    )
