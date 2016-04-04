# QuickHull
A small and brief implementation of the QuickHull algorithm for determining the points in a convex hull in 2D.  
  
Quick Hull is an algorithm with average time complexity of O(nlogn) but in cases where the points are heavily on one side of a split, the algorithm can have a worse case complexity of O(n^2)

## Credits
In no particular order:  
- http://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
- https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
- http://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
- http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html

## License

The MIT License

Copyright (c) 2016 Aaron Batilo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
