build-project:
	mkdir -p build
	cd build && cmake .. && cmake --build .
	echo "" && build/calculator
