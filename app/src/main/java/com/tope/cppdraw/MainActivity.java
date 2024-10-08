package com.tope.cppdraw;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputType;
import android.util.Log;
import android.view.KeyEvent;
import android.text.TextWatcher;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.view.ViewTreeObserver;
import android.widget.Toast;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.graphics.Rect;
import android.content.ClipboardManager;
import android.content.ClipData;

import java.lang.reflect.Field;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MainActivity extends NativeActivity
implements TextWatcher, TextView.OnEditorActionListener
{
    protected View mView;
    private EditText mEditText;
    private Object mutex = new Object();
    private Process daemon = null;

    private native void OnKeyboardShown(int h);
    private native void OnScreenRotation(int deg);
    private native void OnInputCharacter(int ch);
    private native void OnSpecialKey(int code);
    private native void OnProgramOutput(String str);
    private native void OnDeamonStart(int pid);

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        //load native library
        try {
            ActivityInfo ai = getPackageManager().getActivityInfo(
                    getIntent().getComponent(), PackageManager.GET_META_DATA);
            if (ai.metaData != null) {
                String ln = ai.metaData.getString(META_DATA_LIB_NAME);
                System.loadLibrary(ln);
            }
        }
        catch (PackageManager.NameNotFoundException e) {
        }

        //create hidden EditText to access more soft keyboard options
        FrameLayout lay = new FrameLayout(this);
        setContentView(lay, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
        mEditText = new EditText(this);
        mEditText.setOnEditorActionListener(this);
        mEditText.addTextChangedListener(this);
        mEditText.setLayoutParams(new FrameLayout.LayoutParams(1, 1));
        lay.addView(mEditText);
        mView = new View(this);
        mView.setLayoutParams(new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
        lay.addView(mView);

        //install observer to monitor if keyboard is shown
        View mRootView = getWindow().getDecorView().findViewById(android.R.id.content);
        mRootView.getViewTreeObserver().addOnGlobalLayoutListener(
                new ViewTreeObserver.OnGlobalLayoutListener() {
                    public void onGlobalLayout() {
                        View view = getWindow().getDecorView();
                        int screenHeight = view.getRootView().getHeight();
                        Rect r = new Rect();
                        view.getWindowVisibleDisplayFrame(r);
                        //double hkbd = 2.54 * (double)(screenHeight - r.bottom) / getDpi();
                        //boolean kbdShown = hkbd > 3; //kbd height more than 3cm
                        OnKeyboardShown(screenHeight - r.bottom);
                    }
                });
    }

    //@param type - see ImRad::IMEType
    public void showSoftInput(int _type) {
        final int[] actionMap = {
                EditorInfo.IME_ACTION_NONE,
                EditorInfo.IME_ACTION_DONE, EditorInfo.IME_ACTION_GO,
                EditorInfo.IME_ACTION_NEXT, EditorInfo.IME_ACTION_PREVIOUS,
                EditorInfo.IME_ACTION_SEARCH, EditorInfo.IME_ACTION_SEND
        };
        final int type = _type;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                InputMethodManager mgr = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                //int sel1 = mEditText.getSelectionStart();
                //int sel2 = mEditText.getSelectionEnd();
                mEditText.setText("");
                mEditText.setImeOptions(actionMap[type >> 8]);
                mEditText.requestFocus();
                switch (type & 0xff) {
                    case 0:
                        mgr.hideSoftInputFromWindow(mEditText.getWindowToken(), 0);
                        break;
                    default: //ImeText
                        //to enforce NO_SUGGESTIONS we can use TYPE_TEXT_VARIATION_VISIBLE_PASSWORD but then Passwords button may be shown which is weird
                        //mEditText.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS | InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD; //this resets selection
                        //this seems to work better:
                        mEditText.setInputType(InputType.TYPE_NULL);
                        //mEditText.setSelection(sel1, sel2);
                        mgr.showSoftInput(mEditText, InputMethodManager.SHOW_IMPLICIT);
                        break;
                    case 2: //ImeNumber
                        mEditText.setInputType(InputType.TYPE_CLASS_NUMBER); //this resets selection
                        //mEditText.setSelection(sel1, sel2);
                        mgr.showSoftInput(mEditText, InputMethodManager.SHOW_IMPLICIT);
                        break;
                    case 3: //ImeDecimal
                        mEditText.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL); //this resets selection
                        mEditText.setRawInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL); //this resets selection
                        //mEditText.setSelection(sel1, sel2);
                        mgr.showSoftInput(mEditText, InputMethodManager.SHOW_IMPLICIT);
                        break;
                    case 4: //ImePhone
                        mEditText.setInputType(InputType.TYPE_CLASS_PHONE); //this resets selection
                        //mEditText.setSelection(sel1, sel2);
                        mgr.showSoftInput(mEditText, InputMethodManager.SHOW_IMPLICIT);
                        break;
                    case 5: //ImeEmail
                        mEditText.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS); //this resets selection
                        //mEditText.setSelection(sel1, sel2);
                        mgr.showSoftInput(mEditText, InputMethodManager.SHOW_IMPLICIT);
                        break;
                }
            }
        });
    }

    @Override
    public void beforeTextChanged(CharSequence var1, int var2, int var3, int var4) {
    }

    @Override
    public void afterTextChanged(Editable var1) {
    }

    @Override
    public void onTextChanged(CharSequence text, int start, int before, int count) {
        if (count < before)
            OnInputCharacter(0x8); //send backspace
        else if (count == before)
            ; //ignore, f.e. pressing @ in ImeEmail fires this 2x
        else if (count >= 1)
            OnInputCharacter((int)text.charAt(start + count - 1));
    }

    @Override
    public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
        OnSpecialKey(actionId + 1024);
        return true;
    }

    //Use this only for special keys, otherwise not called with IME_TEXT, not called on hw keyboard
    @Override
    public boolean dispatchKeyEvent(KeyEvent ev) {
        //intercept Back button
        if (ev.getAction() == KeyEvent.ACTION_DOWN && ev.getKeyCode() == KeyEvent.KEYCODE_BACK) {
            OnSpecialKey(ev.getKeyCode());
            return false;
        }
        return super.dispatchKeyEvent(ev);
    }
    /*@Override
    public boolean dispatchKeyEvent(KeyEvent ev) {
        if (ev.getAction() == KeyEvent.ACTION_DOWN) {
            int ch = ev.getUnicodeChar(ev.getMetaState());
            if (ch >= 0x20) //control characters handled elsewhere
                unicodeQueue.offer(ch);
        }
        else if (ev.getAction() == KeyEvent.ACTION_MULTIPLE) {
            for (int i = 0; i < ev.getCharacters().length(); ++i) {
                int ch = ev.getCharacters().codePointAt(i);
                if (ch >= 0x20) //control characters handled elsewhere
                    unicodeQueue.offer(ch);
            }
        }
        return super.dispatchKeyEvent(ev);
    }*/

    @Override
    public void onConfigurationChanged(Configuration cfg) {
        super.onConfigurationChanged(cfg);
        int angle = 90 * getWindowManager().getDefaultDisplay().getRotation();
        OnScreenRotation(angle);
    }

    // JNI calls --------------------------------------------------

    public int getDpi() {
        Configuration cfg = getResources().getConfiguration();
        return cfg.densityDpi;
    }
    public int getRotation() {
        int angle = 90 * getWindowManager().getDefaultDisplay().getRotation();
        return angle;
    }
    public void showMessage(String _msg) {
        final String msg = _msg;
        final Activity act = this;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(act, msg, Toast.LENGTH_SHORT);
            }
        });
    }

    public String getClipboardText() {
        ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
        return clipboard.getPrimaryClip().toString();
    }

    public void setClipboardText(String text) {
        ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData clip = ClipData.newPlainText("code", text);
        clipboard.setPrimaryClip(clip);
    }

    public int unzip(String fname, String dstDir) {
        try {
            //unzip STL headers
            File destDir = new File(dstDir);
            byte[] buffer = new byte[1024];
            ZipInputStream zis = new ZipInputStream(new FileInputStream(fname));
            ZipEntry zipEntry = zis.getNextEntry();
            while (zipEntry != null) {
                File destFile = new File(destDir, zipEntry.getName());
                String destDirPath = destDir.getCanonicalPath();
                String destFilePath = destFile.getCanonicalPath();

                if (!destFilePath.startsWith(destDirPath + File.separator)) {
                    throw new java.io.IOException("Entry is outside of the target dir: " + zipEntry.getName());
                }

                if (zipEntry.isDirectory()) {
                    if (!destFile.isDirectory() && !destFile.mkdirs()) {
                        throw new java.io.IOException("Failed to create directory " + destFile);
                    }
                } else {
                    // fix for Windows-created archives
                    File parent = destFile.getParentFile();
                    if (!parent.isDirectory() && !parent.mkdirs()) {
                        throw new java.io.IOException("Failed to create directory " + parent);
                    }

                    // write file content
                    FileOutputStream fos = new FileOutputStream(destFile);
                    int len;
                    while ((len = zis.read(buffer)) > 0) {
                        fos.write(buffer, 0, len);
                    }
                    fos.close();
                }
                zipEntry = zis.getNextEntry();
            }

            zis.closeEntry();
            zis.close();
            return 0;
        } catch (java.lang.Exception e) {
            return 1;
        }
    }

    public void shellExecute(String cmd) {
        Thread th = new Thread() {
            @Override
            public void run() {
                try {
                    Process process = Runtime.getRuntime().exec(cmd);
                    int read;
                    char[] buffer = new char[4096];
                    StringBuffer output = new StringBuffer();

                    BufferedReader reader = new BufferedReader(
                            new InputStreamReader(process.getInputStream()));
                    while ((read = reader.read(buffer)) > 0) {
                        output.append(buffer, 0, read);
                    }
                    reader.close();
                    reader = new BufferedReader(
                            new InputStreamReader(process.getErrorStream()));
                    while ((read = reader.read(buffer)) > 0) {
                        output.append(buffer, 0, read);
                    }
                    reader.close();

                    process.waitFor();
                    OnProgramOutput(output.toString());
                } catch (IOException e) {
                    OnProgramOutput(e.toString());
                } catch (InterruptedException e) {
                    OnProgramOutput(e.toString());
                }
            }
        };
        th.start();
    }

    public void stopDeamon() {
        synchronized (mutex) {
            if (daemon != null) {
                daemon.destroy();
            }
        }
    }

    public void startDeamon(String cmd) {
        stopDeamon();
        Thread th = new Thread() {
            @Override
            public void run() {
                try {
                    int pid = -1;
                    synchronized (mutex) {
                        daemon = Runtime.getRuntime().exec(cmd);
                        Log.i("cppdraw", daemon.toString());
                        try {
                            Field f = daemon.getClass().getDeclaredField("pid");
                            f.setAccessible(true);
                            pid = f.getInt(daemon);
                            f.setAccessible(false);
                        } catch (Throwable e) {
                            pid = -1;
                        }
                    }
                    if (daemon.isAlive()) {
                        Thread.sleep(100);
                        //InputStreamReader rd = new InputStreamReader(daemon.getInputStream());
                        //boolean ready = rd.ready();
                        OnDeamonStart(pid);
                    }
                    /*StringBuffer output = new StringBuffer();
                    BufferedReader readerErr = new BufferedReader(
                            new InputStreamReader(daemon.getErrorStream()));
                    BufferedReader readerIn = new BufferedReader(
                            new InputStreamReader(daemon.getInputStream()));
                    boolean firstRead = true;
                    while (daemon.isAlive()) {
                        while (readerIn.ready())
                            output.append(readerIn.readLine() + "\n");
                        while (readerErr.ready())
                            output.append(readerErr.readLine() + "\n");
                        if (output.length() > 0 && firstRead) {
                            firstRead = false;
                            OnDeamonStart(pid);
                        }
                        Thread.sleep(1);
                    }
                    readerIn.close();
                    readerErr.close();*/

                } catch (InterruptedException e) {
                } catch (IOException e) {
                }
            }
        };
        th.start();
    }
}
