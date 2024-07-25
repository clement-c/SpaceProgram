import bpy
import bmesh
import os


def _bpy_recursive_set(module, dic):
    for key, value in dic.items():
        if isinstance(value, dict):
            curr = getattr(module, key)
            _bpy_recursive_set(curr, value)
        else:
            setattr(module, key, value)


def _bpy_recursive_get(module, dic, result={}):
    for key, value in dic.items():
        if isinstance(value, dict):
            curr = getattr(module, key)
            _bpy_recursive_get(curr, value, result=result.setdefault(key, {}))
        else:
            result[key] = getattr(module, key)
    return result


class BakerBaseClass(object):

    def prepare(self):
        return self

    def bake(self):
        raise NotImplementedError

    def teardown(self):
        return self


class MaterialBaker(BakerBaseClass):

    def __init__(self, texture_resolution=1024, samples=16):
        self._previous_settings = {}
        self._resolution = texture_resolution
        # Setting to set and revert post-bake:
        self._bake_settings = {
            "render": {
                "engine": "CYCLES",
                "bake": {"margin": 4, "use_pass_direct": False, "use_pass_indirect": False},
            },
            "cycles": {"samples": samples},
        }

    def prepare(self):
        self._previous_settings = _bpy_recursive_get(bpy.context.scene, self._bake_settings)
        _bpy_recursive_set(bpy.context.scene, self._bake_settings)
        return super().prepare()

    def bake(self, *materials):
        for material in materials:
            image_name = material.name + "_BakedTexture"
            if image_name in bpy.data.images:
                img = bpy.data.images[image_name]
            else:
                img = bpy.data.images.new(image_name, 1024, 1024)

            nodes = material.node_tree.nodes
            texture_node = nodes.new("ShaderNodeTexImage")
            texture_node.name = "Bake_node"
            texture_node.select = True
            nodes.active = texture_node
            texture_node.image = img

            for output_type in ["Diffuse", "Emit", "Normal"]:
                bpy.ops.object.bake(type=output_type.upper(), save_mode="EXTERNAL")
                img.save_render(
                    filepath=os.path.join(
                        self._folder, "{}_{}.png".format(material.name, output_type)
                    )
                )

            texture_node.select = False

            # delete texture nodes that were created only for export
            nodes.remove(texture_node)

    def teardown(self):
        _bpy_recursive_set(bpy.context.scene, self._previous_settings)
        return super().teardown()


class MeshBaker(BakerBaseClass):

    def bake(self, *meshes):
        for mesh in meshes:
            bm = bmesh.new()
            bm.from_mesh(mesh)
            # bm.transform(mesh.matrix_world)
            bmesh.ops.triangulate(bm, faces=bm.faces, quad_method="BEAUTY", ngon_method="BEAUTY")
            uv_layer = bm.loops.layers.uv.active
            # parse mesh
            for face in bm.faces:
                for loop in face.loops:
                    uv = loop[uv_layer].uv
                    print("Loop UV: %f, %f" % uv[:])
                    vert = loop.vert
                    print("Loop Vert: (%f,%f,%f)" % vert.co[:])
            bm.free()


def export_selection(out_dir : str, export_meshes=True, export_materials=False):
    if not os.path.exists(out_dir):
        print("ERROR: Output directory does not exist ({})".format(out_dir))
        return
    if not os.path.isdir(out_dir):
        print("ERROR: Output path is not a directory ({})".format(out_dir))
        return
    sel_meshes = [m for m in bpy.context.selected_objects if m.type == "MESH"]

    meshes_to_export = []
    materials_to_export = []
    for mesh in sel_meshes:
        if export_meshes:
            meshes_to_export.append(mesh.data)
        if export_materials:
            materials_to_export.append(mesh.active_material)

    out_data = {}

    if meshes_to_export:
        mesh_baker = MeshBaker()
        mesh_baker.prepare()
        out_data["meshes"] = mesh_baker.bake(*meshes_to_export)
        mesh_baker.teardown()

    if export_materials:
        material_baker = MaterialBaker()
        material_baker.prepare()
        out_data["materials"] = material_baker.bake(*materials_to_export)
        material_baker.teardown()


desktop_path = os.path.join(os.path.join(os.path.expanduser('~')), 'Desktop') 
OUTPUT_DIR = os.path.join(desktop_path, "BakeResult")


export_selection(OUTPUT_DIR, export_meshes=True, export_materials=True)


"""
material = bpy.data.materials["Sun_MAT"]
material_node = [node for node in material.node_tree.nodes if node.type == "BSDF_PRINCIPLED"][0]
input_keys = material_node.inputs.keys()
linked_inputs = [socket.name for socket in material_node.inputs if socket.is_linked]
print(linked_inputs)
"""
