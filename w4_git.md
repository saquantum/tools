# Git

`mkdir gitproject`

`git init`

`git add FILE`

`.gitignore`

`git status` shows if there are files to add or changes to commit

`git log` shows commitments with hashcode



##### do a commitment since last commitment:

`git add .`

`git commit -m "COMMITMENT"`

##### checkout

`git checkout HASH`  all files return to that HASH

`git checkout master` return to latest version

##### undo a commitment

`git revert HASH` will add a new commitment.

`git reset HASH` will go back to HASH and clear the latest commitments.



### Setup Instructions

1. **Create a New Branch:**

   ```
   git checkout -b treasure-branch
   ```

2. **Add Commits:**

   - Make several commits (more than three):

     ```
     echo "First commit" > file.txt
     git add file.txt
     git commit -m "First commit"
     
     echo "Second commit" >> file.txt
     git add file.txt
     git commit -m "Second commit"
     
     echo "Third commit" >> file.txt
     git add file.txt
     git commit -m "Third commit"
     
     echo "Here be treasure!" >> file.txt
     git add file.txt
     git commit -m "Here be treasure!"  # The memorable commit
     
     echo "Fourth commit" >> file.txt
     git add file.txt
     git commit -m "Fourth commit"
     
     echo "Fifth commit" >> file.txt
     git add file.txt
     git commit -m "Fifth commit"
     ```

3. **Add More Commits:**

   - Add a few more commits (more than three):

     ```
     echo "Sixth commit" >> file.txt
     git add file.txt
     git commit -m "Sixth commit"
     
     echo "Seventh commit" >> file.txt
     git add file.txt
     git commit -m "Seventh commit"
     
     echo "Eighth commit" >> file.txt
     git add file.txt
     git commit -m "Eighth commit"
     ```

4. **Rebase and Delete the Treasure Commit:**

   - Start an interactive rebase:

     ```
     git rebase -i HEAD~8  # Adjust the number based on your commits
     ```

   - In the editor, you can delete the line with "Here be treasure!" and squash other commits as needed. Save and close the editor to complete the rebase.

### Tasks

#### Task 1: Find the Commit ID of the Vanished Commit

To find the commit ID of the missing commit, use `git reflog`:

```
git reflog
```

To search for the commit message in the reflog output, you can use `grep`:

```
git reflog | grep "Here be treasure!"
```

This will display the entry with the commit ID for the "Here be treasure!" commit.

#### Task 2: Restore the Commit

Once you have the commit ID (let's say it is `abc1234`), you can restore it using the following commands:

1. **Compare Differences:** To see the differences between the treasure commit and the current HEAD, you can use:

   ```
   git diff HEAD abc1234
   ```

2. **Make a Patch:** You can create a patch file to restore the commit:

   ```
   git format-patch -1 abc1234
   ```

3. **Cherry-Pick the Commit:** To restore the commit directly:

   ```
   git cherry-pick abc1234
   ```

#### Task 3: Search for the Missing Commit

If you can't remember the commit message, you can inspect the objects in `.git/objects`. Start with a known commit ID and explore the object structure:

```
git cat-file -p <commit-id>
```

**Script to Search for the Missing Commit:** You can create a simple script to find the missing commit based on your criteria. Here's a basic example in Bash:

```bash
#!/bin/bash
for obj in $(ls .git/objects/*/*); do
    if [ $(git cat-file -t $obj) = "commit" ]; then
        message=$(git cat-file -p $obj | grep "^    " | sed 's/^    //')
        if [[ $message == *"treasure"* ]]; then
            echo "Found commit ID: $obj"
        fi
    fi
done
```

This script iterates through all objects, checks if they are commits, and searches for the word "treasure" in the commit message.

#### Task 4: Understanding `git gc`

The `git gc` command stands for "garbage collection." It cleans up unnecessary files and optimizes the local repository by compressing file history.

- **Why It Makes Recovery Harder:** If `git gc` is run after a commit is deleted, it may remove unreachable objects, including your "Here be treasure!" commit, making it much harder or impossible to recover.
- **When It Gets Run:** Git might automatically run `git gc` during certain operations, especially when you have a lot of loose objects or when you push to a remote repository. You can also manually invoke it:

```
git gc
```

### Summary

By practicing these tasks, you’ll gain a solid understanding of how to manage commits in Git, especially in scenarios where you might accidentally lose important work. Let me know if you have any questions or need further clarification!