# Calculating the Ray

## Important Details
- Our Field of View (FOV) is 60°.

<p align="center">
  <img src="../pic/Fig1_FOV_Field_of_View.png" alt="Field of View">
</p>

## Calculation Steps

### 1. Determine a Grid for the Given Map

A maze like the one shown here can be converted from the given map into a 2D grid map.

<p align="center">
  <img src="../pic/Fig3_given_Map.png" alt="given Map">
</p>

<p align="center">
  <img src="../pic/Fig101_arrow_down_green.png" alt="given Map">
</p>

<p align="center">
  <img src="../pic/Fig40_print_map2.png" alt="given Map">
</p>

<p align="center">
  <img src="../pic/Fig4_print_map2.png" alt="2D_Map">
</p>

### 2. Ray Calculation Process

#### 1. Calculate Vertical Intersections for the Next Column (Fig 5)

<p align="center">
  <img src="../pic/Fig5_Vertical_Intersection.png" alt="calculate vertical">
</p>

Steps for finding intersections with vertical grid lines:

1. Find the coordinates of the first intersection (point B in this example). Since the ray is moving to the right in the image, B.x = rounded_down(Px/64) * (64) + 64. If the ray were moving to the left, B.x = rounded_down(Px/64) * (64) - 1. Calculate A.y = Py + (Px - A.x) * tan(ALPHA).

2. Find Xa. (Note: Xa is just the width of the grid. If the ray is moving to the right, Xa will be positive; if the ray is moving to the left, Xa will be negative.)

3. Find Ya using the equation above.

4. Check the grid at the intersection point. If there is a wall on the grid, stop and calculate the distance.

5. If there is no wall, extend the ray to the next intersection point. Note that the coordinates of the next intersection point (Xnew, Ynew) are simply Xnew = Xold + Xa and Ynew = Yold + Ya.

#### 2. Calculate Horizontal Intersections

<p align="center">
  <img src="../pic/Fig6_Horizontal_Intersection.png" alt="calculate horizontal">
</p>

#### 3. Compare Horizontal and Vertical Intersections

<p align="center">
  <img src="../pic/Fig7_compare_horizontal_vertical.png" alt="compare horizontal and vertical">
</p>

[link](https://permadi.com/1996/05/ray-casting-tutorial-7/)

### Calculate Multiple Rays for the Field of View

<p align="center">
  <img src="../pic/Fig8_FOV_Rays.png">
</p>

