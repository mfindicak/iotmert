import logo from "./logo.svg";
import "./App.css";

import { db } from "./firebase";
import { useEffect, useState } from "react";

import Switch from "@material-ui/core/Switch";
import FormGroup from "@material-ui/core/FormGroup";
import FormControlLabel from "@material-ui/core/FormControlLabel";

function App() {
  const [light, setLight] = useState("");
  const [buzzer, setBuzzer] = useState(false);
  const [motion, setMotion] = useState(false);
  const [humidity, setHumidity] = useState("");
  const [temperature, setTemperature] = useState("");

  const changeBuzzer = async () => {
    db.ref("FirebaseIOT").child("buzzer").set(!buzzer);
  };

  useEffect(() => {
    db.ref("FirebaseIOT").on("value", (snapshot) => {
      setLight(snapshot.child("light").val());
      setBuzzer(snapshot.child("buzzer").val());
      setMotion(snapshot.child("motion").val());
      setHumidity(snapshot.child("humidity").val());
      setTemperature(snapshot.child("temperature").val());
    });
  }, []);
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>Nem: %{humidity}</p>
        <p>Sıcaklık: {temperature} °C</p>
        <p>Işık: {((light / 1024) * 100).toFixed(3)}</p>
        <p>Hareket: {motion ? "Var" : "Yok"}</p>
        {
          <FormGroup>
            <FormControlLabel
              labelPlacement="start"
              control={
                <Switch checked={buzzer} onChange={() => changeBuzzer()} />
              }
              label="Ses"
            />
          </FormGroup>
        }
        <h5 style={{ color: "#61DAFB" }}>
          Mert Şen FINDICAK
          <br /> CITS
        </h5>
      </header>
    </div>
  );
}

export default App;
