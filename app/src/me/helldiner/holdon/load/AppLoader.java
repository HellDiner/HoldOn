package me.helldiner.holdon.load;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

import me.helldiner.holdon.gui.IWindow;
import me.helldiner.holdon.main.Main;

public class AppLoader {
	
	public AppLoader(IWindow window) {
		window.setScreen(new AppLoaderScreen());
		this.loadLibrary("injector");
	}
	
	private void loadLibrary(String name) {
		System.loadLibrary(Main.LIB_DIR+name);
	}
	
	private class AppLoaderScreen extends JPanel {

		private static final long serialVersionUID = 1L;
		
		@Override
		public void paintComponent(Graphics g) {
			g.setColor(Color.WHITE);
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
		}
	}
	
}