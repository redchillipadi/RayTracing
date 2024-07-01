#include "perlin.h"

#include "../random.h"

Perlin::Perlin() {
    for (int i=0; i<pointCount; i++) {
        randVec.emplace_back(Normalise(Vector3::random(-1, 1)));
    }
    
    perm_x = perlinGeneratePerm();
    perm_y = perlinGeneratePerm();
    perm_z = perlinGeneratePerm();
}

double Perlin::noise(const Point3& point) const {
    double u = point.x() - floor(point.x());
    double v = point.y() - floor(point.y());
    double w = point.z() - floor(point.z());

    int i = int(floor(point.x()));
    int j = int(floor(point.y()));
    int k = int(floor(point.z()));
    Vector3 c[2][2][2];

    for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
            for (int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = randVec[
                    perm_x[(i+di) & 255] ^
                    perm_y[(j+dj) & 255] ^
                    perm_z[(k+dk) & 255]
                ];
            }
        }
    }

    return perlinInterpolate(c, u, v, w);
}

double Perlin::turbulence(const Point3& point, int depth) const {
    double accumulator = 0.0;
    Point3 temp = point;
    double weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accumulator += weight * noise(temp);
        weight *= 0.5;
        temp *= 2.0;
    }

    return fabs(accumulator);
}


std::vector<int> Perlin::perlinGeneratePerm() {
    std::vector<int> points(pointCount);

    for (int i = 0; i < pointCount; i++)
        points.emplace_back(i);

    permute(points);

    return std::move(points);
}

void Perlin::permute(std::vector<int>& points) {
    for (int i = points.size() - 1; i > 0; i--) {
        int target = randomInt(0, i);
        int temp = points[i];
        points[i] = points[target];
        points[target] = temp;
    }
}

double Perlin::perlinInterpolate(const Vector3 c[2][2][2], double u, double v, double w) {
    double uu = u * u * (3 - 2 * u);
    double vv = v * v * (3 - 2 * v);
    double ww = w * w * (3 - 2 * w);
    double accumulator = 0.0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                Vector3 weightV(u-i, v-j, w-k);
                accumulator += (i * uu + (1 - i) * (1 - uu))
                            *  (j * vv + (1 - j) * (1 - vv))
                            *  (k * ww + (1 - k) * (1 - ww))
                            *  Dot(c[i][j][k], weightV);
            }
        }
    }

    return accumulator;
}

