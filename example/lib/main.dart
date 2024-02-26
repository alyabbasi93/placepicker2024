import 'package:flutter/material.dart';
import 'package:placepicker2024/entities/location_result.dart';
import 'package:placepicker2024/widgets/place_picker.dart';


void main() {
  runApp(MyApp());
}



class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return  MaterialApp(
          home: PickerDemo(),
        );
  }
}

class PickerDemo extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => PickerDemoState();
}

class PickerDemoState extends State<PickerDemo> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Picker Location 2024')),
      body: Center(
        child: MaterialButton(
          child: Text("Pick location"),
          onPressed: () {
            showPlacePicker();
          },
        ),
      ),
    );
  }

  void showPlacePicker() async {
    LocationResult? result = await Navigator.of(context).push(
        MaterialPageRoute(builder: (context) => PlacePicker("YOUR API KEY")));

    // Handle the result in your way
    print(result);
  }
}