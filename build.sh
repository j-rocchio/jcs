make_test=false
make_lib=false

for arg in "$@";
do
	if [ "$arg" == "clean" ]; then
		rm -rf build
		rm -rf output
		rm -rf test/test
	fi

	if [ "$arg" == "lib" ]; then
		make_lib=true
  	fi

	if [ "$arg" == "test" ]; then
		make_test=true
  	fi
done

if [ "$make_lib" == true ]; then
	mkdir -p build
	mkdir -p output
	cd build
	cmake ..
	cmake --build . --target jcs_shared jcs_static
	mv libjcs* ../output
	cd ..
fi

if [ "$make_test" == true ]; then
	mkdir -p build
	cd build
	cmake ..
	cmake --build . --target test
	./test
	mv test ../test
	cd ..
fi