package busta.quest;

import java.applet.Applet;
import java.awt.BorderLayout;

public class QuestApplet extends Applet{
	private static final long serialVersionUID = 1L;
	
	private QuestComponent questComponent = new QuestComponent();
	
	public void init(){
		setLayout(new BorderLayout());
		add(questComponent, BorderLayout.CENTER);
	}
	public void start(){
		questComponent.start();
	}
	public void stop(){
		questComponent.stop();
	}
}
