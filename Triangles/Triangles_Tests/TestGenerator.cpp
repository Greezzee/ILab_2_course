#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

float EPS = 0.000001f;

struct Point
{
    float x, y, z;
};

/*
Creates line of right angled triangles, lx, ly - lenght of side. 
Starts from {0, 0, 0} (point woth right angle) and make a step dist_vector to draw next triangle
Can create dublicates (guarantee collide) or outsiders (guarantee not collide) with
probability of dublicates_per and outsider_per
*/
void GenerateLineTest(int test_id, size_t count, float lx, float ly, Point dist_vector, int dublicates_per = 0, int outsider_per = 0)
{
    bool isCollide = false;
    if (fabsf(dist_vector.z) < EPS &&
        (dist_vector.x > 0 && dist_vector.y > 0 && dist_vector.x / lx + dist_vector.y / ly < 1) ||
        (dist_vector.x < 0 && dist_vector.y < 0 && -dist_vector.x / lx - dist_vector.y / ly < 1) ||
        (dist_vector.x < 0 && dist_vector.y > 0 && -dist_vector.x < lx) ||
        (dist_vector.x > 0 && dist_vector.y < 0 && -dist_vector.y < ly))
        isCollide = true;

    std::ofstream question, answer;

    question.open("./Tests/" + std::to_string(test_id) + ".test");
    answer.open("./Tests/" + std::to_string(test_id) + ".ans");

    Point base = {0, 0, 0}, buf = base;
    bool outsider_flag = false;
    question << count << "\n\n";
    for (size_t i = 0; i < count; i++) {

        if (std::rand() % 100 < outsider_per && !outsider_flag) {

            buf.x += dist_vector.x > 0 ? -2 * (lx + ly) : 2 * (lx + ly);
            buf.y += dist_vector.y > 0 ? 2 * (lx + ly) : - 2 * (lx + ly);

            outsider_flag = true;

            question << buf.x << " " << buf.y << " " << buf.z << "\n";
            question << buf.x + lx << " " << buf.y << " " << buf.z << "\n";
            question << buf.x << " " << buf.y + ly << " " << buf.z << "\n";
            question << "\n";
            if (test_id == 9)
                std::cout << i << " ";
            continue;
        }
        outsider_flag = false;
        question << base.x << " " << base.y << " " << base.z << "\n";
        question << base.x + lx << " " << base.y << " " << base.z << "\n";
        question << base.x << " " << base.y + ly << " " << base.z << "\n";
        question << "\n";

        if (isCollide)
            answer << i << "\n";

        else if (std::rand() % 100 < dublicates_per && i + 1 != count) {
            i++;
            question << base.x << " " << base.y << " " << base.z << "\n";
            question << base.x + lx << " " << base.y << " " << base.z << "\n";
            question << base.x << " " << base.y + ly << " " << base.z << "\n";
            question << "\n";
            if(!isCollide) {
                answer << i - 1 << "\n";
                answer << i << "\n";
            }
        }

        base.x += dist_vector.x;
        base.y += dist_vector.y;
        base.z += dist_vector.z;

    }

    question.close();
    answer.close();
}


void GeneratePairsTest(int test_id, size_t count, float max_side, int pair_per)
{
    float z = 0;
    std::ofstream question, answer;

    question.open("./Tests/" + std::to_string(test_id) + ".test");
    answer.open("./Tests/" + std::to_string(test_id) + ".ans");

    question << count << "\n";

    for (size_t i = 0; i < count; i++) {
        Point a, b, c;
        a = b = c = {0, 0, z};

        a.x -= (float)(std::rand() % 1000) / 1000.f * max_side;
        a.y += (float)(std::rand() % 1000) / 1000.f * max_side;

        b.x += (float)(std::rand() % 1000) / 1000.f * max_side;
        b.y += (float)(std::rand() % 1000) / 1000.f * max_side;

        c.y -= (float)(std::rand() % 1000) / 1000.f * max_side;

        question << a.x << " " << a.y << " " << a.z << "\n";
        question << b.x << " " << b.y << " " << b.z << "\n";
        question << c.x << " " << c.y << " " << c.z << "\n";
        question << "\n";

        if (std::rand() % 100 < pair_per && i + 1 < count) {
            i++;

            question << a.x / 2 << " " << a.y / 2 << " " << a.z << "\n";
            question << b.x / 2 << " " << b.y / 2 << " " << b.z << "\n";
            question << c.x / 2 << " " << c.y / 2 << " " << c.z << "\n";
            question << "\n";

            answer << i - 1 << "\n";
            answer << i << "\n";
        }
        z += 0.1;
    }
    question.close();
    answer.close();
}



int main() {

    for(size_t i = 1; i <= 3; i++) {
        float x = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float y = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float dist = std::min(x, y) / 2.1f;
        GenerateLineTest(i, 1000, x, y, {(std::rand() % 1000) / 1000.f * dist, (std::rand() % 1000) / 1000.f * dist, 0}, 0, 0);
    }

    for(size_t i = 4; i <= 6; i++) {
        float x = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float y = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float dist = std::max(x, y);
        GenerateLineTest(i, 1000, x, y, {(std::rand() % 1000) / 1000.f * dist, (std::rand() % 1000) / 1000.f * dist, 0}, 20, 20);
    }

    for(size_t i = 7; i <= 9; i++) {
        float x = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float y = (float)(std::rand() % 1000000) / 10000.f + 0.1f;
        float dist = std::max(x, y);
        GenerateLineTest(i, 1000, x, y, {(std::rand() % 1000) / 1000.f * dist, (std::rand() % 1000) / 1000.f * dist, (std::rand() % 1000) / 1000.f}, 5, 0);
    }

    for (size_t i = 10; i < 13; i++)
        GeneratePairsTest(i, 1000, std::rand() % 50, std::rand() % 40 + 10);

    return 0;
}