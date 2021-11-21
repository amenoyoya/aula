--- FileSystem library ---

-- Scan directory
-- @param {string} dir
-- @param {function(name string, path string, ...)->boolean} callback
-- @param {...} extra arguments for the callback function
-- @returns {boolean}
function fs.scandir(dir, callback, ...)
    debug.checkarg(2, dir, "string", callback, "function")
    local dirent = fs.dir_open(dir)
    if dirent == nil then return false end
    repeat
        if not callback(dirent.current_name, dirent.current_path, ...) then
            dirent:close()
            return false
        end
    until not dirent:next()
    dirent:close()
    return true
end

-- @private Enumerate files|directories base function
local function enumfiles(name, path, dest, nest, mode)
    if name == ".." or name == "." or nest == 0 then return true end
    local info = {
        path = path,
        isfile = fs.path.isfile(path),
        isdir = fs.path.isdir(path),
    }
    if info.isfile then
        if mode ~= "dir" then
            dest[#dest + 1] = info
        end
    elseif info.isdir then
        if mode ~= "file" then
            dest[#dest + 1] = info
        end
        return fs.scandir(info.path, enumfiles, dest, nest - 1, mode)
    end
    return true
end

-- Enumerate files|directories in the directory
-- @param {string} dir: target directory
-- @param {number} nest: recursive enumeration nest (default: -1 => infite), 0 => no enumeration
-- @param {string} mode: "all"(default) | "file" | "dir"
-- @returns {table[]} {name: string, path: string, isfile: boolean, isdir: boolean}[]
function fs.enumfiles(dir, nest, mode)
    local files = {}
    return fs.scandir(dir, enumfiles, files, nest == nil and -1 or nest, mode or "all") and files or {}
end
