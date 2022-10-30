#pragma once

class LineEditor : public ShapeEditor {
	void OnLBdown(HWND);
	void OnMouseMove(HWND);
	void OnLBup(HWND);
	void OnInitMenuPopup(HWND, WPARAM);

};
