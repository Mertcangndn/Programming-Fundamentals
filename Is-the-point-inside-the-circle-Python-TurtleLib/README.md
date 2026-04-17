
# Circle Point Checker with Turtle Graphics

This Python program uses the Turtle graphics library to visualize and check if a given point is inside or outside a circle based on user input.

## How It Works

1. **User Input**: The program prompts the user to enter:
   - The radius of the circle (`r`).
   - The x and y coordinates of a point.

2. **Mathematical Check**: 
   - Calculates if the point lies inside or outside the circle by comparing the squared distance from the origin (0,0) to the squared radius. 
   - If the squared distance `(x^2 + y^2)` is less than or equal to `r^2`, the point is inside; otherwise, it's outside.

3. **Visualization**:
   - Draws a circle with radius `r` centered at the origin.
   - Marks the point location in black for easy reference.

## Running the Program

Ensure that Python and the Turtle graphics library are installed. Run the code, and after entering the required values, the result (inside or outside) will be displayed in the terminal, and a visual representation of the circle and point will appear.

## Example

Input:
```
Radius (r): 50
Point (x, y): 30, 40
```

Output:
- Terminal: "The point is inside the circle."
- Graphical: The circle and point marked on screen.

## Requirements

- Python 3.x
- Turtle graphics library

## License

This code is provided under the MIT License.
