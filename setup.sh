#bash

# Step 1: Install SFML and dependencies
echo "Installing SFML and dependencies..."
sudo apt-get update
sudo apt-get install -y libsfml-dev

# Step 2: Clean build directory
echo "Cleaning build directory..."
BUILD_DIR="build"
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"

# Step 3: Run cmake and make
echo "Running cmake and make..."
cd "$BUILD_DIR"
cmake ..
make

echo "Setup complete!"
