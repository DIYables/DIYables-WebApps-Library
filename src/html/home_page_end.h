#ifndef HOME_PAGE_END_HTML_H
#define HOME_PAGE_END_HTML_H

const char HOME_PAGE_END_HTML[] PROGMEM = R"HTMLDELIM(</div><div class="status"><h4>Connection Status</h4><div class="status-info"><div class="status-item"><strong>HTTP:</strong><span id="httpPort">80</span></div><div class="status-item"><strong>WebSocket:</strong><span id="wsPort">81</span></div><div class="status-item"><strong>IP:</strong><span id="ipAddress">Loading...</span></div></div></div><div class="footer"><p>Powered by DIYables WebApp Library</p></div></div><script>document.getElementById('ipAddress').textContent=window.location.hostname;</script></body></html>)HTMLDELIM";

#endif
