# Day 16: The Floor Will Be Lava

### Part One
Today's problem includes a grid of mirrors of different angles that split and reflect light differently. A beam of light only travels horizontally or vertically. If it hits a perpindicular mirror, it splits off into two beams. If it hits a diagonal, it turns 90-degrees left or right depending on the mirror.

To begin, we can parse our input into a grid of `char`s. I also set some constants specific to `input.txt`.

```c++
#include <iostream>
#include <fstream>
using namespace std;

const int GRID_WIDTH = 110;
const int GRID_HEIGHT = 110;

int main() {
    char grid[GRID_HEIGHT][GRID_WIDTH];

    ifstream fin("input.txt");

    string s;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        getline(fin, s);
        for (int c = 0; c < GRID_WIDTH; c++)
            grid[r][c] = s[c];
    }

    fin.close();

    return 0;
}
```

Our task is the count the number of energized spaces, which is anywhere a beam passes at least once. The initial beam of light enters at the top-left corner facing right. 

We can definitely simulate this problem as our grid isn't that big at all. The tricky part is to not double count our energized spaces. We can make a two-dimensional boolean array to track whether a space have been energized.

```c++
bool energized[GRID_HEIGHT][GRID_WIDTH];
for (int r = 0; r < GRID_HEIGHT; r++)
    for (int c = 0; c < GRID_WIDTH; c++)
        energized[r][c] = false;
```

Now let's write the simulation. We can't simulate this with a simple loop because when the beams split we have multiple beams of light to keep track of. Instead, let's do this with recursion. 

I'm going to write a `beam` function that takes in our grid, `grid`, the originating row, `r`, and column, `c`, and the direction in which the beam is traveling.

```c++
void beam(char grid[GRID_HEIGHT][GRID_WIDTH], int r, int c);
```

Wait, how should I represent the directions? I'll use an enumeraion to make it nicer.

```c++
enum dir {UP, DOWN, LEFT, RIGHT};

void beam(char grid[GRID_HEIGHT][GRID_WIDTH], int r, int c, dir d);
```

Let's make sure we understand what this recursive step includes. I want it to travel in its direction on the grid, until it hits a mirror. Based off of the mirror type, it will call a new `beam`(s). If our beam had hit the edge of the grid, it would return. Lastly, at each step of the beam's life, it would be updating our energized grid.

Ah, that reminds me, we'll have to also pass our energized grid as a parameter so the `beam` function can see it.

```c++
void beam(char grid[GRID_HEIGHT][GRID_WIDTH], bool energized[GRID_HEIGHT][GRID_WIDTH], int r, int c, dir d);
```

I'll call this function as if a beam started from just outside the grid, like so:

```c++
beam(grid, energized, 0, -1, RIGHT);
```


Time to write it! Let's use a do-while loop to ensure our beam moves off the mirror from where we started the beam.

```c++
do {
    //move
    energized[r][c] = true;

} while (grid[r][c] == '.');
```

To move, we just basically increment or decrement our row or column. We can do this with four if-statements, but a switch-case might be cleaner. I'm going to wrap this into a helper function to make things look nicer.

```c++
void step(int &r, int &c, dir d) {
    switch (d) {
        case UP: r--;
        case DOWN: r++;
        case LEFT: c--;
        case RIGHT: c++;
    }
}
```

Now we have this simple `beam` traveling function.

```c++
do {
    step(r, c, d);
    energized[r][c] = true;
} while (grid[r][c] == '.');
```

Of course, there is more to add as we don't want to go out of bounds, and the `beam` function doesn't even call itself yet.

After a step, if we fall out of bounds, we return. The beam of light disappears.

```c++
do {
    step(r, c, d);

    if (r < 0 || r >= GRID_HEIGHT || c < 0 || c >= GRID_WIDTH) 
        return;
    
    energized[r][c] = true;
} while (grid[r][c] == '.');
```

Now to make more beams of light appear! A set of if-statements can work for us here. But, I'm just gonna use a `switch` for fun.

```c++
switch (grid[r][c]) {
    case '|':

    case '-':

    case '/':

    case '\\':

}  
```

For the first two, if the direction is perpindicular to the mirror, it splits into two beams. Otherwise, if the beam of light is parallel to the mirror, it passes through it. We can interpret that as a new beam of light in the same direction.

```c++
case '|':
    if (d == UP || d == DOWN) {
        beam(grid, energized, r, c, d);
    } else {
        beam(grid, energized, r, c, UP);
        beam(grid, energized, r, c, DOWN);
    }
    break;
case '-':
    if (d == LEFT || d == RIGHT) {
        beam(grid, energized, r, c, d);
    } else {
        beam(grid, energized, r, c, LEFT);
        beam(grid, energized, r, c, RIGHT);
    }
    break;
```

For the next two, we kinda have to just hard-code it. More `switch` statements :D.

```c++
case '/':
    switch (d) {
        case UP: beam(grid, energized, r, c, RIGHT);
        case DOWN: beam(grid, energized, r, c, LEFT);
        case LEFT: beam(grid, energized, r, c, DOWN);
        case RIGHT: beam(grid, energized, r, c, UP);
    }
    break;
case '\\':
    switch (d) {
        case UP: beam(grid, energized, r, c, LEFT);
        case DOWN: beam(grid, energized, r, c, RIGHT);
        case LEFT: beam(grid, energized, r, c, UP);
        case RIGHT: beam(grid, energized, r, c, DOWN);
    }
    break;
```

When I run the code, I get... a segmentation fault. I probably tried to access a row/column that was out of bounds of the grid. Printing out the row and column of every beam call, I see a whole lot of `22 0`s. Why is our beam staying in place? Is it our `step` function?

A simple test of the `step` function reveals that something is amiss. 
```c++
int r = 1;
int c = 2;

step(r, c, UP);
cout << r << " " << c << endl; //produces 1 2

step(r, c, RIGHT);
cout << r << " " << c << endl; //produces 1 3
```

How strange, I wouldn't expected to see `0 2` and `1 3`. The only thing the step function really is, is a switch statement. A quick google reveals that without a `break` statement, each case that follows will be run regardless if it had satisfied it or not. Welp. This is what I get for trying to be cool.

I added `break`s back wherever it was needed. And now...

Still a segmentation fault... At least this time we're actually moving around the grid.

```
14 9 < 
12 9
18 9
18 8
16 8
14 8
14 9 <
12 9
18 9
18 8
16 8
14 8
14 9 <
12 9
18 9
```
See it loop? We've probably exhausted our resources. How can we stop sending beams that we've already created? Let's make a set to keep track of beam combinations, namely the row, column and direction.

```c++
#include <unordered_set>

unordered_set<string> cache;

...
    //in beam function
    if (cache.find(to_string(r) + to_string(c) + to_string(d)) != cache.end())
        return;
    else 
        cache.insert(to_string(r) + to_string(c) + to_string(d));
```

No more segmentation faults! Let's count the number of energized spots.

```c++
int numEnergized = 0;
for (int r = 0; r < GRID_HEIGHT; r++)
    for (int c = 0; c < GRID_WIDTH; c++)
        numEnergized += energized[r][c];

cout << numEnergized << endl;
```

We end up with the answer of `6994` for part one.

### Part Two

For part two, we are to find the maximum energization of any configuration of starting beams. So instead of starting from the top, we can start on any edge tile, in its corresponding direction.

Let's try every configuration and track the max!

```c++
int maxEnergized = 0;

for (int i = 0; i < GRID_HEIGHT; i++) {
    bool energized[GRID_HEIGHT][GRID_WIDTH];
    for (int r = 0; r < GRID_HEIGHT; r++)
        for (int c = 0; c < GRID_WIDTH; c++)
            energized[r][c] = false;

    beam(grid, energized, i, -1, RIGHT);
    
    //count number of energized tiles
    int numEnergized = 0;
    for (int r = 0; r < GRID_HEIGHT; r++)
        for (int c = 0; c < GRID_WIDTH; c++)
            numEnergized += energized[r][c];
    
    maxEnergized = max(maxEnergized, numEnergized);

    cache.clear();
}

cout << maxEnergized << endl;
//repeat for three other edges
```

We end up with the answer of `7488` for part two.