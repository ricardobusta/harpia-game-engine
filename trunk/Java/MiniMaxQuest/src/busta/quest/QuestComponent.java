package busta.quest;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class QuestComponent extends Canvas implements Runnable {
	private static final long serialVersionUID = 1L;
	
	private static final int WIDTH = 100;
	private static final int HEIGHT = 100;
	private static final int SCALE = 4;
	
	private boolean running;
	private Thread thread;
	
	//private Game game;

	public QuestComponent() {
		Dimension size = new Dimension(WIDTH*SCALE,HEIGHT*SCALE);
		setSize(size);
		setPreferredSize(size);
		setMinimumSize(size);
		setMaximumSize(size);
	}
	
	public void run() {

	}
	
	public void start(){
		if(running) return;
		running = true;
		thread = new Thread(this);
		thread.start();
	}
	
	public void stop(){
		if(!running) return;
		running = false;
		try{
			thread.join();
		}catch(InterruptedException e){
			e.printStackTrace();
		}
	}
	
	public static void main(String[] arg){
		QuestComponent game = new QuestComponent();
		
		JFrame frame = new JFrame("Teste");
		
		JPanel panel = new JPanel(new BorderLayout());
		panel.add(game,BorderLayout.CENTER);
		
		frame.setContentPane(panel);
		frame.pack();
		frame.setLocationRelativeTo(null);
		frame.setResizable(false);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

		game.start();
	}
}
