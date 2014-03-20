g++ naive.cpp -o naive
g++ divide_conquer.cpp -o divide_conquer
g++ build_left.cpp -o build_left
g++ math.cpp -o math
echo "===========================NAIVE======================"
time ./naive
echo "======================DIVIDE-CONQUER=================="
time ./divide_conquer
echo "========================BUILD-LEFT===================="
time ./build_left
echo "============================MATH======================"
time ./math
