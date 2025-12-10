@tool
extends SceneTree

# Configuration
const SOURCE_DIR = "res://entities/player/data"
const TARGET_DIR = "res://converted_abilities"

func _init():
	print("Starting MGAS Conversion...")
	
	# Create target directory
	var dir = DirAccess.open("res://")
	if not dir.dir_exists(TARGET_DIR):
		dir.make_dir_recursive(TARGET_DIR)
	
	convert_directory(SOURCE_DIR)
	
	print("Conversion Complete! check " + TARGET_DIR)
	quit()

func convert_directory(path: String):
	var dir = DirAccess.open(path)
	if not dir:
		print("Error accessing: " + path)
		return

	dir.list_dir_begin()
	var file_name = dir.get_next()
	
	while file_name != "":
		if dir.current_is_dir():
			if file_name != "." and file_name != "..":
				convert_directory(path + "/" + file_name)
		else:
			if file_name.ends_with(".tres"):
				process_file(path + "/" + file_name)
		
		file_name = dir.get_next()

func process_file(file_path: String):
	var file = FileAccess.open(file_path, FileAccess.READ)
	if not file:
		return
		
	var content = file.get_as_text()
	
	# Naive Check if it's a State resource (by name or content)
	# Legacy files have 'script_class="State"' or 'script = ExtResource(... state.gd ...)'
	# But we rely on text since valid scripts might be missing.
	
	if "script_class=\"State\"" in content or "state.gd" in content:
		convert_state(file_path, content)
	elif "script_class=\"Item\"" in content or "item.gd" in content:
		convert_item(file_path, content)
	else:
		pass # Unknown or irrelevant

func convert_state(path: String, content: String):
	print("Converting State: " + path)
	
	var name_regex = RegEx.new()
	name_regex.compile("name\\s*=\\s*\"([^\"]+)\"")
	
	var state_name = "UnknownAbility"
	var result = name_regex.search(content)
	if result:
		state_name = result.get_string(1)
		
	# Create new MachiGameplayAbility
	var ability = MachiGameplayAbility.new()
	ability.resource_name = state_name
	
	# Try to generate a tag
	# Folder structure: .../states/bow/Idle.tres -> Ability.Bow.Idle
	var parts = path.replace(".tres", "").split("/")
	var category = parts[parts.size() - 2].capitalize()
	var name_clean = parts[parts.size() - 1].capitalize()
	
	# Create simple tag (Note: In real app, tags should be registered centrally)
	# For now we just set the resource name to be descriptive
	ability.resource_name = "GA_" + category + "_" + name_clean
	
	# Determine logical path
	var save_path = TARGET_DIR + "/" + category + "/"
	var dir = DirAccess.open("res://")
	if not dir.dir_exists(save_path):
		dir.make_dir_recursive(save_path)
		
	var final_path = save_path + "GA_" + name_clean + ".tres"
	ResourceSaver.save(ability, final_path)
	print("Saved to: " + final_path)

func convert_item(path: String, content: String):
	print("Converting Item: " + path)
	# Items in MGAS are often GameplayEffects that grant abilities or Attributes
	# For now, let's create a placeholder Ability that represents "Equipping" this item?
	# Or maybe just skip items for now as they are complex.
	# Let's map Item -> MachiAttributeSet (just as a placeholder for stats)?
	# User requested "convert all resources".
	
	var name_regex = RegEx.new()
	name_regex.compile("name\\s*=\\s*\"([^\"]+)\"")
	var item_name = "UnknownItem"
	var result = name_regex.search(content)
	if result:
		item_name = result.get_string(1)
	
	# We'll treat Items as GameplayEffects for now (granting stats)
	var effect = MachiGameplayEffect.new()
	effect.resource_name = "GE_Item_" + item_name
	
	var save_path = TARGET_DIR + "/Items/"
	var dir = DirAccess.open("res://")
	if not dir.dir_exists(save_path):
		dir.make_dir_recursive(save_path)
		
	ResourceSaver.save(effect, save_path + "GE_" + item_name + ".tres")
	print("Saved Item as Effect: " + save_path + "GE_" + item_name + ".tres")
