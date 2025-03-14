# Git指令

### 1. **确认当前目录是否是 Git 仓库**

运行以下命令检查当前目录是否是 Git 仓库：

```bash
git status
```

### 2. **初始化一个新的 Git 仓库**

如果当前目录不是 Git 仓库，你可以将其初始化为一个新的 Git 仓库：

```bash
git init
```

这会在当前目录下创建一个 `.git` 文件夹，表示该目录已经是一个 Git 仓库

### 3. **克隆一个现有的 Git 仓库**

如果你是想在一个现有的远程仓库中工作，可以使用 `git clone` 命令将远程仓库克隆到本地：

bash

复制

```
git clone <远程仓库的URL>
```

例如：

```
git clone https://github.com/你的用户名/你的仓库名.git
```

这会将远程仓库的内容下载到当前目录，并自动将其初始化为 Git 仓库。

------

### 4. **检查是否在正确的目录中操作**

如果你已经初始化了 Git 仓库，但仍然遇到这个错误，可能是因为你在错误的目录中运行了 Git 命令。确保你进入了正确的目录：

```
cd /path/to/your/repository
```

然后再次运行 Git 命令。

------

### 5. **检查父目录是否是 Git 仓库**

Git 会从当前目录向上查找 `.git` 文件夹。如果你在一个子目录中操作，但父目录是 Git 仓库，Git 仍然可以正常工作。你可以运行以下命令检查：

```bash
git rev-parse --show-toplevel
```

这会显示当前 Git 仓库的根目录路径。









#### 1. **添加未跟踪的文件到暂存区**

如果你希望将 `PicGo_config/` 文件夹添加到 Git 仓库中，可以运行以下命令：

```
git add PicGo_config/
```

这将把 `PicGo_config/` 文件夹及其内容添加到暂存区。

------

#### 2. **提交更改**

将文件添加到暂存区后，你需要提交这些更改：

```
git commit -m "添加 PicGo_config 文件夹"
```

------

#### 3. **推送到远程仓库**

如果你希望将这些更改推送到远程仓库（例如 GitHub），可以运行：

```
git push origin main
```

------

#### 4. **忽略未跟踪的文件（可选）**

如果你不希望跟踪 `PicGo_config/` 文件夹，可以通过 `.gitignore` 文件将其忽略：

1. 创建或编辑 `.gitignore` 文件：

   ```
   nano .gitignore
   ```

2. 在文件中添加以下内容：

   ```
   PicGo_config/
   ```

3. 保存并退出编辑器。

这样，`PicGo_config/` 文件夹将不会被 Git 跟踪。

------

#### 5. **检查状态**

完成上述操作后，你可以再次运行 `git status` 检查仓库状态：

```
git status
```

如果没有其他未跟踪的文件或未提交的更改，输出应该是：

```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```







要确认你的本地仓库是否是最新状态，以及如何拉取远程仓库的最新更改，可以按照以下步骤操作：

------

### 1. **检查本地仓库状态**

运行以下命令查看当前分支的状态：

```
git status
```

如果输出显示 `Your branch is up to date with 'origin/main'`，说明你的本地分支已经与远程分支同步，是最新状态。

如果显示 `Your branch is behind 'origin/main'`，说明本地分支落后于远程分支，需要拉取最新更改。

------

### 2. **拉取远程仓库的最新更改**

如果本地分支落后于远程分支，可以使用以下命令拉取最新更改：

```
git pull origin main
```

- `git pull` 会自动从远程仓库（`origin`）的 `main` 分支拉取最新更改，并尝试合并到当前分支。
- 如果有冲突，Git 会提示你解决冲突。

------

### 3. **查看远程仓库的更新**

如果你想查看远程仓库是否有更新，而不直接拉取，可以使用：

```
git fetch origin
```

- `git fetch` 会从远程仓库下载最新的提交和分支信息，但不会自动合并到本地分支。

- 运行后，你可以通过以下命令比较本地分支和远程分支的差异：

  ```
  git log main..origin/main --oneline
  ```

  这会显示远程分支有而本地分支没有的提交。

------

### 4. **合并远程更改**

如果你使用了 `git fetch`，可以手动合并远程分支的更改：

```
git merge origin/main
```

这会将 `origin/main` 的更改合并到当前分支。

------

### 5. **解决冲突（如果有）**

如果在拉取或合并过程中出现冲突，Git 会提示你哪些文件有冲突。你需要手动解决冲突：

1. 打开冲突文件，找到冲突标记（`<<<<<<<`、`=======`、`>>>>>>>`）。

2. 修改文件，保留需要的更改，删除冲突标记。

3. 保存文件后，将解决冲突的文件添加到暂存区：

   ```
   git add <冲突文件>
   ```

4. 完成冲突解决后，提交更改：

   ```
   git commit -m "解决合并冲突"
   ```

------

### 6. **总结**

- 使用 `git status` 检查本地分支是否是最新状态。
- 使用 `git pull origin main` 拉取远程仓库的最新更改。
- 使用 `git fetch` 查看远程仓库的更新，然后手动合并。
- 如果有冲突，手动解决冲突并提交。







# 锋哥git使用教程

```bash
git add .
git commit -m "my modify"
    
git pull		//拉取最新分支
git checkout -b personal/zhangfeng/uart

vi wx_main.c

//esc退出编辑，:wq


git status

git add .

//创建两个新文件
vi a.c
vi b.c
//查看修改了哪些文件
git status

git add a.c
git add b.c
//不想修改了，回退本地上一个版本
git restore --staged a.c


//上交本地仓库
git commit -m "i add two file and modify the wx_main.c"

//查找日志
git log

//压缩日志
git rebase -i HEAD-3  (压缩几条命令)

//再次上传
git push

//强推到远端
git push -f 


//切到主线分支
git checkout master
git pull


git merge master
git status


git merge --commit



//rebase方法解决冲突

git checkout master
git pull
git checkout personal/zhangfeng
git rebase master


//删除分支
git branch -D 分支名





```

撤销工作目录中所有未提交的更改，将其恢复到最近一次提交的状态。

```mark
# 撤销所有更改
git checkout -- .
```















### 1. 创建并切换到新的 `personal/cuijingtao/cam_ip` 分支

使用以下命令创建并切换到新分支：

bash

复制

```
git checkout -b personal/cuijingtao/cam_ip
```

### 2. 推送新分支到远程仓库

创建并切换到新分支后，将其推送到远程仓库：

bash

复制

```
git push -u origin personal/cuijingtao/cam_ip
```

### 3. 确认分支创建成功

使用以下命令查看所有分支，确认新分支已成功创建并推送到远程仓库：

bash

复制

```
git branch -a
```

你应该能在输出中看到 `remotes/origin/personal/cuijingtao/cam_ip`，表示分支已成功创建并推送。

### 总结

- 创建并切换到新分支：`git checkout -b personal/cuijingtao/cam_ip`
- 推送分支到远程仓库：`git push -u origin personal/cuijingtao/cam_ip`
- 确认分支创建成功：`git branch -a`

希望这些步骤能帮助你成功创建并管理你的 `personal/cuijingtao/cam_ip` 分支！





























# git diff

``` bash
git diff
```

`git diff` 是 Git 版本控制系统中一个非常重要且常用的命令，主要用于查看文件内容的差异。以下从不同方面详细介绍它：

### 基本功能

`git diff` 最核心的功能是对比文件或提交之间的差异，通过输出结果能清晰看到文件内容在不同状态下的修改情况，包括新增、删除和修改的行。

### 常见使用场景及示例

#### 1. 比较工作区和暂存区的差异

当你对工作区的文件进行了修改，但还未使用 `git add` 命令将这些修改添加到暂存区时，可以使用以下命令查看差异：

```bash
git diff
```

示例：假设你修改了 `test.txt` 文件，执行该命令后，会显示 `test.txt` 文件在工作区的修改内容与暂存区版本的差异。

#### 2. 比较暂存区和本地仓库的差异

如果你已经使用 `git add` 将修改添加到了暂存区，但还没有使用 `git commit` 提交到本地仓库，想查看暂存区与最新提交之间的差异，可以使用：

```bash
git diff --staged
```

在一些较旧的 Git 版本中，也可以使用 `git diff --cached` 达到相同效果。

#### 3. 比较两个提交之间的差异

若要查看两个不同提交之间文件内容的差异，可以指定提交的哈希值或分支名：

```bash
git diff <commit1> <commit2>
```

例如，查看 `HEAD`（当前所在分支的最新提交）和上一次提交之间的差异：

```bash
git diff HEAD^ HEAD
```

这里 `HEAD^` 表示 `HEAD` 的父提交。

#### 4. 比较不同分支之间的差异

如果想了解两个不同分支之间文件内容的差异，可以这样使用：

```bash
git diff <branch1> <branch2>
```

比如，查看 `master` 分支和 `feature` 分支的差异：

```bash
git diff master feature
```

### 输出格式说明

`git diff` 的输出结果遵循一定的格式，以下是一个简单示例：

plaintext

```plaintext
diff --git a/test.txt b/test.txt
index 4b825dc..d670469 100644
--- a/test.txt
+++ b/test.txt
@@ -1,2 +1,3 @@
 This is the first line.
+This is a new line.
 This is the second line.
```

- `diff --git a/test.txt b/test.txt`：表明正在比较的文件是 `test.txt`。
- `index 4b825dc..d670469 100644`：显示文件在不同版本中的哈希值。
- `--- a/test.txt`：表示文件的旧版本。
- `+++ b/test.txt`：表示文件的新版本。
- `@@ -1,2 +1,3 @@`：这是一个块头，`-1,2` 表示旧版本从第 1 行开始的 2 行，`+1,3` 表示新版本从第 1 行开始的 3 行。
- `-` 开头的行：表示在旧版本中有，但新版本中删除的行。
- `+` 开头的行：表示在新版本中新增的行。

### 总结

`git diff` 是一个强大的工具，能帮助开发者清晰了解文件内容的变化情况，在代码审查、问题排查和版本管理等方面发挥着重要作用。

如何解决git pull合并冲突？

详细介绍git diff的参数及用法

除了git diff，还有哪些工具可以比较文件差异？

