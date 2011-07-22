#ifndef LISTENERH
#define LISTENERH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���


//�����ؤ��Y���
namespace gui {
    namespace event {

	class WindowListener {
	  public:
	    virtual void windowClosing(TObject * Sender, TCloseAction & Action) = 0;
	    virtual void windowActivated(TObject * Sender, TCloseAction & Action) = 0;
	    virtual void windowDeactivated(TObject * Sender, TCloseAction & Action) = 0;
	};

	class WindowAdapter:public WindowListener {
	  public:
	    virtual void windowClosing(TObject * Sender, TCloseAction & Action);
	    virtual void windowActivated(TObject * Sender, TCloseAction & Action);
	    virtual void windowDeactivated(TObject * Sender, TCloseAction & Action);
	};
	class MouseListener {
	  public:
	    virtual void mousePressed(TObject * Sender,
				      TMouseButton Button, TShiftState Shift, int X, int Y) = 0;
	    virtual void mouseReleased(TObject * Sender,
				       TMouseButton Button, TShiftState Shift, int X, int Y) = 0;
	};
	class MouseMotionListener {
	  public:
	    virtual void mouseMoved(TObject * Sender, TShiftState Shift, int X, int Y) = 0;
	};

	class ChangeListener {
	  public:
	    virtual void stateChanged(TObject * Sender) = 0;
	};

	class ListSelectionListener {
	  public:
	    virtual void valueChanged(TObject * Sender, int ACol, int ARow, bool & CanSelect) = 0;
	};
    };
};
#endif

