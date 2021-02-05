#version 330 core

in vec3 fNormal;
in vec3 fPos;
in vec2 ftexCoord;

uniform vec3 eye;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	vec3 direction; // For spotlight
	float cutoff;
	float out_cutoff;
};
uniform Light light;

// light_mode:
// 0 - Directional
// 1 - Point
// 2 - Spotlight
uniform int light_mode;

out vec4 out_color;

void main(void)
{
	vec3 diffuse = vec3(0.0);
	vec3 ambient = vec3(0.0);
	vec3 specular = vec3(0.0);

	// Directional light
	if (light_mode == 0)
	{
		// Ambient
		ambient = ambient = light.ambient * vec3(texture(material.diffuse, ftexCoord));

		// Normal
		vec3 norm = normalize(fNormal);

		vec3 light_dir = normalize(light.direction);

		// Diffuse
		float diff = max(dot(norm, light_dir), 0.0);
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ftexCoord));

		// Specular
		vec3 view_dir = normalize(eye - fPos);
		vec3 reflect_dir = reflect(-light_dir, norm);

		// Calculating the reflection direction for each fragment is heavy, so we can use half vector (Blinn-Phong Lighting Model)
		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
		specular = spec * light.specular * vec3(texture(material.specular, ftexCoord));
	}

	// Point light
	else if (light_mode == 1)
	{
		// Attenuation
		float distance = length(light.position - fPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

		// Ambient
		ambient = light.ambient * vec3(texture(material.diffuse, ftexCoord));

		// Normal
		vec3 norm = normalize(fNormal);

		vec3 light_dir = normalize(light.position - fPos);

		// Diffuse
		float diff = max(dot(norm, light_dir), 0.0);
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ftexCoord));
		diffuse = diffuse * 10; // For see the attenation better

		// Specular
		vec3 view_dir = normalize(eye - fPos);
		vec3 reflect_dir = reflect(-light_dir, norm);
		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
		specular = spec * light.specular * vec3(texture(material.specular, ftexCoord));

		ambient  *= attenuation;
		diffuse  *= attenuation;
		specular *= attenuation;
	}

	// Spotlight
	else if (light_mode == 2)
	{
		// Ambient
		ambient = light.ambient * vec3(texture(material.diffuse, ftexCoord));

		// Normal
		vec3 norm = normalize(fNormal);

		vec3 light_dir = normalize(eye - fPos);

		// Diffuse
		float diff = max(dot(norm, light_dir), 0.0);
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ftexCoord));

		// Specular
		vec3 view_dir = normalize(eye - fPos);
		vec3 reflect_dir = reflect(-light_dir, norm);
		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
		specular = spec * light.specular * vec3(texture(material.specular, ftexCoord));

		float theta = dot(light_dir, normalize(light.direction));
		float epsilon = light.cutoff - light.out_cutoff;
		float intensity = clamp((theta - light.out_cutoff) / epsilon, 0.0, 1.0);

		diffuse *= intensity;
		specular *= intensity;
	}
	
	vec3 result = (ambient + diffuse + specular);

	out_color = vec4(result, 1.0);
}
