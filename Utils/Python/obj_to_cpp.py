import os

def parse_obj(obj_path : str) -> dict:
    lines = []
    dst_dir, obj_file = os.path.split(obj_path)
    with open(obj_path, 'r') as f:
        lines = f.readlines()
    obj_name = "mesh"
    points = []
    texture_coords = []
    normals = []
    faces = []
    for line in lines:
        line = line.strip()
        if line.startswith('o '):
            obj_name = line.split()[1]
        if line.startswith('v '):
            points.append([float(v) for v in line.split()[1:]])
        if line.startswith('vt '):
            texture_coords.append([float(v) for v in line.split()[1:]])
        if line.startswith('vn '):
            normals.append([float(v) for v in line.split()[1:]])
        if line.startswith('f '):
            faces.append([[int(f) for f in v.split('/')] for v in line.split(' ')[1:]])

    result = [f"float {obj_name}[] = {{\n"]
    for face in faces:
        # print("face", face)
        for j in list(range(3)):
            # print("face[j]", face[j])
            pt = points[face[j][0] - 1]
            t = texture_coords[face[j][1] - 1]
            n = normals[face[j][2] - 1]
            # print("pt", pt)
            # print("t", pt)
            # print("n", pt)
            result .append("    {}, {}, {}, {}, {}, {}, {}, {},\n".format(pt[0], pt[1], pt[2], t[0], t[1], n[0], n[1], n[2]))
    result.append("};\n")
    out_hpp_file = os.path.join(dst_dir, os.path.splitext(obj_file)[0] + ".hpp")
    with open(out_hpp_file, 'w+') as f:
        f.writelines(result)

if __name__ == "__main__":
    import sys
    obj_path = sys.argv[1]
    obj = parse_obj(obj_path)
