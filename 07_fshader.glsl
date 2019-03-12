#version 330

in vec4 fragPosition;
in vec4 fragColor;
in vec2 tex;
in vec3 fragNormal;
in vec4 eye;

out vec4 color;

uniform sampler2D texture1;
uniform int tex_or_color;
uniform int light1_on;
uniform int light2_on;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main () 
{
	// Defining Materials
	// light 1
	vec4 diffuse_mat = vec4(1, 1, 1, 1.0);
	vec4 ambient_mat = vec4(1, 1, 1, 1.0);
	vec4 specular_mat = vec4(1.0, 1.0, 1.0, 1.0);
	float shininess = 10.0;
	float ambient_coefficient = 0.2;
	float attenuation_coefficient = 0.001;

	vec4 lightPos = vec4(0, 7, -8, 0.0);
	vec4 surfaceToLight = lightPos + eye;

	// light 2
	vec4 diffuse_mat2 = vec4(1, 1, 0, 1.0);
	vec4 specular_mat2 = vec4(1.0, 1.0, 0, 1.0);
	float shininess2 = 10.0;
	float attenuation_coefficient2 = 0.005;

	vec4 lightPos2 = vec4(-2, 0, -8, 0.0);
	vec4 surfaceToLight2 = lightPos + eye;

	vec4 frag_color = fragColor;
	if(tex_or_color == 0){
	    frag_color = fragColor;
	  }
	  else{
		frag_color = texture(texture1, tex);
		//frag_color = color;
	  }

	// ambient
	vec3 ambient = ambient_coefficient * frag_color.rgb;

	// diffuse
	vec3 n = normalize(normalMatrix * normalize(fragNormal));

	// LIGHT 1
	float dotProduct = dot(n, normalize(vec3(surfaceToLight)));
	float intensity = max(dotProduct, 0.0);
	vec3 diffuse = intensity * frag_color.rgb * diffuse_mat.xyz;

	// Compute specular component only if light falls on vertex
	vec4 specular = vec4(0.0);
	if(intensity > 0.0)
	{
		vec3 e = normalize(vec3(eye));
		vec3 h = normalize(normalize(vec3(surfaceToLight)) );
		float intSpec = max(dot(h,n), 0.0);	
		specular = specular_mat * frag_color * pow(intSpec, shininess);
	}

	// attenuation
	float attenuation = 1.0 / (1.0 + (attenuation_coefficient * pow(length(surfaceToLight), 2)));

	// LIGHT 2
	float dotProduct2 = dot(n, normalize(vec3(surfaceToLight2)));
	float intensity2 = max(dotProduct2, 0.0);
	vec3 diffuse2 = intensity2 * frag_color.rgb * diffuse_mat2.xyz;

	// Compute specular component only if light falls on vertex
	vec4 specular2 = vec4(0.0);
	if(intensity2 > 0.0)
	{
		vec3 e = normalize(vec3(eye));
		vec3 h = normalize(normalize(vec3(surfaceToLight2)) );
		float intSpec = max(dot(h,n), 0.0);	
		specular2 = specular_mat2 * frag_color * pow(intSpec, shininess2);
	}

	// attenuation
	float attenuation2 = 1.0 / (1.0 + (attenuation_coefficient2 * pow(length(surfaceToLight2), 2)));

	vec3 contrib1 = light1_on * attenuation * (diffuse + vec3(specular));
	vec3 contrib2 = light2_on * attenuation2 * (diffuse2 + vec3(specular2));
	vec3 linearColor = ambient + ((contrib1 + contrib2) / 2.0);
	// vec3 linearColor = diffuse;

	color = vec4(linearColor, fragColor.a);
}
