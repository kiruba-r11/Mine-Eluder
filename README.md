# Mine-Eluder
A 2-D grid based game, partially using the rules and concepts of the famous game "`Minesweeper`".

## Intro about the Game
`Mine Eluder` is a `2-D grid` based game with some cells having obstacles. Initially all the cells are covered. 
The goal of the game is to uncover all the possible cells that do not have obstacles. 
The player can step into any location inside the grid and uncover it. 
The obstacles are called as `mines`, where the player should not step into, if he steps into the mine and uncovers it, then the game ends there. 
There are three difficulty levels in this game, `Newbie`, `Specialist` and `Master`. 
The `dimension` of grid and `probability` of mines is determined according to the `difficulty level`.  
  
## Rules of the Game
1. The rule of the game is to uncover all the cells that do not have `mines` in it.
2. To uncover any cell you may enter the cell location. If the cell you entered has mine it in, then you lose the game, else the game continues.
3. You can choose the difficulty of the game. There are three difficulty options available. They are
   
      - `NEWBIE`
      - `SPECIALIST`
      - `MASTER`
      
4. Symbols used and its meaning 

      - It represents `*` -> `Mine`
      - It represents `-` -> `Closed Location`
      - It represents `O` -> `Uncovered Location`
      
## Configuration of the Grid
#### 1. Dimension of the Grid
<table>
  <tr>
    <td> NEWBIE </td> 
    <td> 5*5 </td> 
    <td> (Total 25 cells) </td>
  </tr>
  <tr>
    <td> SPECIALIST </td> 
    <td> 7*7 </td> 
    <td> (Total 49 cells) </td>
  </tr>
  <tr>
    <td> MASTER </td> 
    <td> 9*9 </td> 
    <td> (Total 81 cells) </td>
  </tr>
</table>

#### 2. Probability of Mines
<table>
  <tr>
    <td> NEWBIE </td> 
    <td> 0.20 </td> 
    <td> (Total 5 mines in 25 cells) </td>
  </tr>
  <tr>
    <td> SPECIALIST </td> 
    <td> 0.30 </td> 
    <td> (Total 15 mines in 49 cells) </td>
  </tr>
  <tr>
    <td> MASTER </td> 
    <td> 0.40 </td> 
    <td> (Total 33 mines in 81 cells) </td>
  </tr>
</table>

## Concepts Used
- `vector` -> `C++ STL`
- `string` -> `C++`
- `random` function
- `class` and `object`

## Approach Used
The grid is implemented as a `Sparse Matrix` where `mines` are the `non-zero` elements and `other cells` are the `zero` elements. This Sparse Matrix is represented in memory using `2-D vector` based on `coordinate list` method where row and column of mines location is stored. This thereby saves `^((1 - 2 * p) * 100)%` of memory. The locations of non-zero elements in the Sparse Matrix is filled using the `random` function present in the `Standard Library`.

^ `(p - probability of mines)` -> the `result` is `approximate` value

### Spoiler :wink:
It is a `luck-based` game. So, if you are not able to win it, don't worry! There is a `CHEAT CODE` option where you can enter the cheat and `reveal` the location of mines before the start of the game.

### Pull Requests
I am open to PRs and would really appreciate you to contribute to this repository. 

**_Note:_ I developed this game as an app which is an upgradation to this command-line application with a good UI. You can find the App code here :point_right: [Click Here](https://github.com/kiruba-r11/Mine-Eluder-App)**
