/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUICOREDECORATOR_H
#define RMLUICOREDECORATOR_H

#include <vector>
#include "Header.h"
#include "Texture.h"
#include "Types.h"

namespace Rml {
namespace Core {

class DecoratorInstancer;
class Element;
class PropertyDictionary;
class Property;
struct Texture;

/**
	The abstract base class for any visual object that can be attached to any element.

	@author Peter Curry
 */

class RMLUICORE_API Decorator
{
public:
	Decorator();
	virtual ~Decorator();

	/// Called on a decorator to generate any required per-element data for a newly decorated element.
	/// @param[in] element The newly decorated element.
	/// @return A handle to a decorator-defined data handle, or nullptr if none is needed for the element.
	virtual DecoratorDataHandle GenerateElementData(Element* element) const = 0;
	/// Called to release element data generated by this decorator.
	/// @param[in] element_data The element data handle to release.
	virtual void ReleaseElementData(DecoratorDataHandle element_data) const = 0;

	/// Called to render the decorator on an element.
	/// @param[in] element The element to render the decorator on.
	/// @param[in] element_data The handle to the data generated by the decorator for the element.
	virtual void RenderElement(Element* element, DecoratorDataHandle element_data) const = 0;

	/// Value specifying an invalid or non-existent Decorator data handle.
	static const DecoratorDataHandle INVALID_DECORATORDATAHANDLE = 0;

protected:
	/// Attempts to load a texture into the list of textures in use by the decorator.
	/// @param[in] texture_name The name of the texture to load.
	/// @param[in] rcss_path The RCSS file the decorator definition was loaded from; this is used to resolve relative paths.
	/// @return The index of the texture if the load was successful, or -1 if the load failed.
	int LoadTexture(const String& texture_name, const String& rcss_path);
	/// Adds a texture if it is valid into the list of textures in use by the decorator.
	/// @param[in] texture The texture to add.
	/// @return The index of the texture if it is successful, or -1 if it is invalid.
	int AddTexture(const Texture& texture);
	/// Get number of textures in use by the decorator.
	int GetNumTextures() const;
	/// Returns one of the decorator's previously loaded textures.
	/// @param[in] index The index of the desired texture.
	/// @return The texture at the appropriate index, or nullptr if the index was invalid.
	const Texture* GetTexture(int index = 0) const;

private:
	// Stores a list of textures in use by this decorator.
	// Optimized for the common case of a single texture.
	Texture first_texture;
	std::vector< Texture > additional_textures;
};

}
}

#endif
