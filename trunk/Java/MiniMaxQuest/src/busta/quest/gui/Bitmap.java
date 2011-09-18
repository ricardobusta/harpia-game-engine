package busta.quest.gui;

import java.awt.image.BufferedImage;

import javax.imageio.ImageIO;

public class Bitmap {
	public final int width;
	public final int height;
	public final int[] pixel;

	Bitmap(int width, int height) {
		this.width = width;
		this.height = height;
		pixel = new int[width * height];
	}

	Bitmap(String fileName) {
		try {
			BufferedImage img = ImageIO.read(Bitmap.class.getResource(fileName));
			width = img.getWidth();
			height = img.getHeight();
			pixel = new int[width * height];

			img.getRGB(0, 0, width, height, pixel, 0, width);
			for (int i = 0; i < pixel.length; i++) {
				pixel[i] = ((pixel[i] & 0xf) >> 2);
			}
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	void setAlphaColor(int col) {
		for (int i = 0; i < pixel.length; i++) {
			if (pixel[i] == col) {
				pixel[i] = -1;
			}
		}
	}

	void fill(int x0, int y0, int x1, int y1, int color) {
		for (int y = y0; y < y1; y++) {
			for (int x = x0; x < x1; x++) {
				pixel[x + (y * width)] = color;
			}
		}
	}
}
