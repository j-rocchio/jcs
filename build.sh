make_lib=false
make_test=false
make_gen=false

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

  	if [ "$arg" == "gen" ]; then
		make_gen=true
  	fi
done

if [ "$make_lib" == true ]; then
	mkdir -p build
	mkdir -p output
	cd build
	cmake ..
	cmake --build . --target jcs_shared jcs_static
	mv libjcs* ../output
	\cp -a ../src/*h ../output
	cd ..
fi

if [ "$make_gen" == true ]; then
	mkdir -p build
	cd build
	cmake ..
	cmake --build . --target jcs_gen
	mv jcs_gen ../output
	cd ..
fi

if [ "$make_test" == true ]; then
	mkdir -p build
	cd build
	cmake ..
	cmake --build . --target test
	mv test ../test
	cd ../test
	./test
	cd ..
fi