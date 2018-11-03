const fs = require('fs');
const path = require('path');

function fail(msg) {
  console.error('FAIL ' + msg);
  process.exit(1);
}

const src = fs.readFileSync(path.join(__dirname, '..', 'SGWhatsApp.h'), 'utf8');
if (!src.includes('GROUP_API_SERVER\t\tL"api.whatsmate.net"') && !src.includes('api.whatsmate.net')) fail('host');
if (!src.includes('/v3/whatsapp/group/text/message/12')) fail('path');
if (!src.includes('class SGWhatsApp')) fail('cls');
if (!src.includes('bool SendGroupMessage')) fail('send');
console.log('OK WhatsAppMateTests');
