/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	D3DGraphics.h																		  *
 *	Copyright 2014 PlanetChili <http://www.planetchili.net>								  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <d3d9.h>
#include "GdiPlusManager.h"
#include "Vec2.h"
#include "Rect.h"
#include "Colors.h"
#include "DrawTarget.h"
#include "Surface.h"

class D3DGraphics : public DrawTarget
{
public:
	D3DGraphics( HWND hWnd );
	~D3DGraphics( );
	template< typename T >
	inline Color GetPixel( _Vec2<T> p ) const
	{
		return GetPixel( (int)p.x,(int)p.y );
	}
	inline Color GetPixel( int x,int y ) const;
	template< typename T >
	inline void PutPixel( _Vec2<T> p,Color c )
	{
		PutPixel( (int)p.x,(int)p.y,c );
	}
	inline void PutPixel( int x,int y,Color c );
	template< typename T >
	inline void PutPixelAlpha( _Vec2<T> p,Color c )
	{
		PutPixelAlpha( (int)p.x,(int)p.y,c );
	}
	inline void PutPixelAlpha( int x,int y,Color c );
	template< typename T >
	inline void DrawLine( _Vec2<T> p0, _Vec2<T> p1,Color c )
	{
		DrawLine( (int)p0.x,(int)p0.y,(int)p1.x,(int)p1.y,c );
	}
	void DrawLine( int x0,int y0,int x1,int y1,Color c );
	void DrawLineClip( Vec2 p0,Vec2 p1,Color color,const RectF& clip );
	template< typename T >
	inline void DrawCircle( _Vec2<T> center,int radius,Color c )
	{
		DrawCircle( (int)center.x,(int)center.y,radius,c );
	}
	void DrawCircle( int centerX,int centerY,int radius,Color c );
	template< typename T >
	inline void DrawCircleClip( _Vec2<T> center,int radius,const RectI& clip,Color c )
	{
		DrawCircleClip( (int)center.x,(int)center.y,radius,clip,c );
	}
	void DrawCircleClip( int centerX,int centerY,int radius,const RectI& clip,Color c );
	template< typename T >
	inline void DrawFilledCircleClip( _Vec2<T> center,int radius,const RectI& clip,Color c )
	{
		DrawFilledCircleClip( (int)center.x,(int)center.y,radius,clip,c );
	}
	void DrawFilledCircleClip( int centerX,int centerY,int radius,const RectI& clip,Color color );
	void DrawTriangle( Vec2 p0,Vec2 p1,Vec2 p2,const RectI& clip,Color c );
	inline void DrawString( const std::wstring& string,Vec2 pt,const Font& font,Color c = WHITE )
	{
		sysBuffer.DrawString( string,pt,font,c );
	}
	inline void DrawString( const std::wstring& string,const RectF &rect,const Font& font,Color c = WHITE,Surface::Alignment a = Surface::Center  )
	{
		sysBuffer.DrawString( string,rect,font,c,a );
	}
	void BeginFrame();
	void EndFrame();
	virtual void Draw( Drawable& obj ) override
	{
		obj.Rasterize( *this );
	}
public:
	static RectI GetScreenRect()
	{
		return { 0,SCREENHEIGHT - 1,0,SCREENWIDTH - 1 };
	}
	static const unsigned int	SCREENWIDTH =	1280;
	static const unsigned int	SCREENHEIGHT =	720;
private:
	void DrawFlatTriangle( float y1,float y2,float m1,float m2,
		float b1,float b2,const RectI& clip,Color c );
private:
	GdiPlusManager		gdiPlusManager;
	const Color			FILLVALUE =	BLACK;
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	IDirect3DSurface9*	pBackBuffer;
	Surface				sysBuffer;
};