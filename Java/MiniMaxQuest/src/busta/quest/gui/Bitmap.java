package busta.quest.gui;

import java.awt.image.BufferedImage;

import javax.imageio.ImageIO;

public class Bitmap {
	public final int width;
	public final int height;
	public final int[] pixels;

	public Bitmap(int width, int height) {
		this.width = width;
		this.height = height;
		pixels = new int[width * height];
	}

	public Bitmap(String fileName) {
		try {
//			BufferedImage img = ImageIO.read(Bitmap.class.getResource(fileName));
			BufferedImage img = ImageIO.read(Bitmap.class.getResource(fileName));
			width = img.getWidth();
			height = img.getHeight();
			pixels = new int[width * height];

			img.getRGB(0, 0, width, height, pixels, 0, width);
			for (int i = 0; i < pixels.length; i++) {
				pixels[i] = ((pixels[i] & 0xf) >> 2);
			}
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
	
	public Bitmap(String fileName, int alphaColor){
		this(fileName);
		setAlphaColor(alphaColor);
	}

	void setAlphaColor(int alphaColor) {
		for (int i = 0; i < pixels.length; i++) {
			if (pixels[i] == alphaColor) {
				pixels[i] = -1;
			}
		}
	}

	void fill(int x0, int y0, int x1, int y1, int color) {
		for (int y = y0; y < y1; y++) {
			for (int x = x0; x < x1; x++) {
				pixels[x + (y * width)] = color;
			}
		}
	}
}
