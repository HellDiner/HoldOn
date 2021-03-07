package me.helldiner.holdon.gui;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;

import me.helldiner.holdon.main.Main;

public class Window extends JFrame implements IWindow, WindowListener {
	
	private static final long serialVersionUID = 1L;
	private List<WindowStateListener> stateListeners = new ArrayList<WindowStateListener>();

	public Window() {
		this.init();
	}
	
	private void init() {
		final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		this.setTitle(Main.APP_NAME+" v"+Main.APP_VERSION+" - "+Main.AUTHOR_NAME);
		this.setSize((int)(screenSize.getWidth()/8D*7), (int)(screenSize.getHeight()/8D*7));
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.addWindowListener(this);
		this.setVisible(true);
	}

	@Override
	public void addStateListener(WindowStateListener listener) {
		this.stateListeners.add(listener);
	}
	
	@Override
	public void setScreen(Container screen) {
		this.setContentPane(screen);
	}
	
	@Override
	public void windowActivated(WindowEvent e) {}

	@Override
	public void windowClosed(WindowEvent e) {}

	@Override
	public void windowClosing(WindowEvent e) {
		for(WindowStateListener listener : this.stateListeners) listener.onWindowClosing();
	}

	@Override
	public void windowDeactivated(WindowEvent e) {}

	@Override
	public void windowDeiconified(WindowEvent e) {}

	@Override
	public void windowIconified(WindowEvent e) {}

	@Override
	public void windowOpened(WindowEvent e) {}
	
}