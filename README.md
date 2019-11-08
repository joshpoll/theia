# Theia with SML Backend

## Rule Checklist
- [x] 90
- [x] 91
- [x] 92
- [x] 93
- [x] 94
- [x] 95
- [x] 96
- [ ] 97
- [ ] 98
- [ ] 99
- [ ] 100
- [x] 101
- [x] 102
- [ ] 103
- [ ] 104
- [ ] 105
- [ ] 106
- [ ] 107
- [x] 108
- [x] 109
- [x] 110
- [x] 111
- [x] 112
- [x] 113
- [x] 114
- [ ] 115
- [ ] 116
- [ ] 117
- [ ] 118
- [ ] 119
- [ ] 120
- [ ] 121
- [ ] 122
- [ ] 123
- [ ] 124
- [ ] 125
- [ ] 126
- [ ] 127
- [ ] 128
- [ ] 129
- [ ] 130
- [ ] 131
- [ ] 132
- [ ] 133
- [ ] 134
- [ ] 135
- [ ] 136
- [ ] 137
- [ ] 138
- [ ] 139
- [ ] 140
- [ ] 141
- [ ] 142
- [x] 143
- [ ] 144
- [ ] 145
- [ ] 146
- [ ] 147
- [ ] 148
- [ ] 149
- [ ] 150
- [ ] 151
- [ ] 152
- [ ] 153
- [ ] 154
- [ ] 155
- [x] 156
- [ ] 157
- [ ] 158
- [ ] 159
- [x] 160
- [ ] 161
- [ ] 162
- [ ] 163
- [ ] 164
- [ ] 165
- [ ] 166
- [ ] 167
- [ ] 168
- [ ] 169
- [ ] 170
- [ ] 171
- [ ] 172
- [ ] 173
- [ ] 174
- [ ] 175
- [ ] 176
- [ ] 177
- [ ] 178
- [ ] 179
- [ ] 180
- [ ] 181
- [ ] 182
- [ ] 183
- [ ] 184
- [ ] 185
- [ ] 186
- [ ] 187
- [ ] 188
- [ ] 189

## Run

```sh
cd src/server/hamlet
make # using your favorite SML implementation
cd -
npm install
npm run server
# in a new tab
npm start
# in a new tab
cd src/server
python3 server.py # requires Python 3.7. TODO: This is probably missing some dependencies right now.
```

Open a new web page to `http://localhost:8000/`. Change any `.re` file in `src` to see the page auto-reload. **You don't need any bundler when you're developing**!

**How come we don't need any bundler during development**? We highly encourage you to open up `index.html` to check for yourself!

# Bundle for Production

We've included a convenience `UNUSED_webpack.config.js`, in case you want to ship your project to production. You can rename and/or remove that in favor of other bundlers, e.g. Rollup.

We've also provided a barebone `indexProduction.html`, to serve your bundle.

```sh
npm install webpack webpack-cli
# rename file
mv UNUSED_webpack.config.js webpack.config.js
# call webpack to bundle for production
./node_modules/.bin/webpack
open indexProduction.html
```
