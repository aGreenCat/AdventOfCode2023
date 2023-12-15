# Day 11: Cosmic Expansion

### Part One
Today's problem includes a grid of galaxies sitting in space, and we are to measure distances beween galaxies after the expansion of space. We are told that space expands in an empty row or column by adding an adjacent duplicate.

Immediately, notice that the distances we need are not Euclidean distances, but *Manhattan distances*. Thus, given the coordinates of two galaxies, the distance between the two is simple the sum of the differences in row and column.

In order to operate over each *pair* of galaxies, we can first keep a list of galaxy coordinates in a list. Then, for each galaxy in the list, find its Manhattan distance to each galaxy after it in the list. This way, we hit every possible pairing without duplicates. We also do **not** need to compute the number of pairs, which would be `n*(n-1)/2` where `n` is the number of galaxies.

Don't forget, we need to take the expanding space into account. We have some options. We can modify our grid and then add the altered coordinates to our list of galaxies. We can also take our expanding space into account as we calculate distance, because the Manhattan distance conveniently always increases by `1` when a row or column expands between two galaxies. That's because difference in row/column increases by one, the duplicated row/column.

In either approach, we will have to first go through the grid and keep a track of empty columns and empty rows. In the first approach, we can traverse our grid in search of galaxies, while keeping count of how many empty rows/columns we passed, adding the corresponding count to a galaxy's coordinates when we append it to our list. This is very doable. The second approach would have to check every row and column in between two galaxies and then adjust the distance, which is not terrible but a bit more tedious and uneccessary. Let's just do the first one. 

I'm going to choose C++ for this task for more order in my code and just because we won't be changing the size of our grid or working with strings.

Our first step is to parse our input, and I'm going to put this data into a two-dimensional boolean array. I'm using booleans because there's only two states to this grid, galaxy or space (`true` or `false`).
```c++
bool grid[GRID_HEIGHT][GRID_WIDTH];

string s;
for (int r = 0; r < GRID_HEIGHT; r++) {
    getline(fin, s);
    for (int c = 0; c < GRID_WIDTH; c++) {
        grid[r][c] = s[c] == '#';
    }
}
```
Now, it's time to find those empty columns and rows. I'm going to use sets to keep track of them so we can access in constant time. We can technically use an array or vector paired with an index variable because we can guarantee them to be ordered due to our traversal, but that's extra work than needed. Simple nested for loops here.
```c++
unordered_set<int> empty_rows;
unordered_set<int> empty_cols;

for (int r = 0; r < GRID_HEIGHT; r++) {
    bool empty = true;
    for (int c = 0; c < GRID_WIDTH; c++) {
        if (grid[r][c]) {
            empty = false;
            break;
        }
    }

    if (empty) empty_rows.insert(r);
}

for (int c = 0; c < GRID_WIDTH; c++) {
    bool empty = true;
    for (int r = 0; r < GRID_WIDTH; r++) {
        if (grid[r][c]) {
            empty = false;
            break;
        }
    }

    if (empty) empty_cols.insert(c);
}
```
With that, we'll move on and make a list of galaxies. I'm going to use a vector because we don't need to know how many galaxies there are exactly, nor do we need to specifically index each galaxy. But we're not quite there yet! We also need to decide what type the vector holds as well. We could use std::pair for coordinates, but I think I'm just going to make a small `struct` here. It'll look nicer :\).
```c++
struct Coord {
    int r;
    int c;
};
```
Cool. Let's go through our grid and add the coordinates to a `Coord` vector. Remember, we need to take into account the space expansion. I'll use two variables to account for the offset in the rows and columns.
```c++
vector<Coord> galaxy_coords;

int r_offset = 0;
for (int r = 0; r < GRID_HEIGHT; r++) {
    // If row is empty, add to offset and continue
    // There are no galaxies in an empty row
    if (empty_rows.find(r) != empty_rows.end()) {
        r_offset++;
        continue;
    }

    int c_offset = 0;
    for (int c = 0; c < GRID_WIDTH; c++) {
        if (empty_cols.find(c) != empty_cols.end()) {
            c_offset++;
        }
        
        if (grid[r][c]) galaxy_coords.push_back(Coord{r + r_offset, c + c_offset});
    }
}
```
Now let's go through all the pairs of coordinates in the array. We'll have a total distance variable and add the Manhattan distance of each pair of galaxies
```c++
int total_dists = 0;

for (int i = 0; i < galaxy_coords.size(); i++) {
    Coord first_coord = galaxy_coords[i];
    for (int j = i+1; j < galaxy_coords.size(); j++) {
        Coord second_coord = galaxy_coords[j];
        int man_dist = abs(first_coord.r - second_coord.r) + abs(first_coord.c - second_coord.c);
        total_dists += man_dist;
    }
}

cout << total_dists << endl;
```
We are good for part one!

### Part Two

Part two modifies the problem, specifically the expansion factor. Instead of doubling, the amound of space increases by a factor of million. Everything else remains the same. 

Let's try updating how much we increase our offsets from 1 to 999,999.
```c++
const int EXPANSION = 999999;
...

if (grid[r][c]) galaxy_coords.push_back(Coord{r + r_offset*EXPANSION, c + c_offset*EXPANSION});
```
It... doesn't quite work. After some debugging, I found that the total_dists variable went **negative** at times by printing its value every time it got updated. This is likely just an overflow error. Let's use a different type for our total_dists variable, like a `long long int`.

The answer for part two will reveal itself after that. Day 11 completed!